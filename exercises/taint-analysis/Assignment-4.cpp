/********************************************************************************************************************
 * NOTE: This assignment was completed by the collaborative efforts of Group 19.
********************************************************************************************************************/

#include "Assignment-4.h"
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <string>

using namespace SVF;
using namespace llvm;
using namespace std;


// Get sources function names read from checker_source_api collected from a text file
std::set<const CallICFGNode *>& TaintGraphTraversal::identifySources()
{
    for (const CallICFGNode *cs : pag->getCallSiteSet())
    {
        const SVFFunction *fun = SVFUtil::getCallee(cs->getCallSite());
        if (checker_source_api.find(fun->getName()) != checker_source_api.end())
        {
            sources.insert(cs);
        }
    }
    return sources;
}
// Get sinks function names read from checker_sink_api collected from a text file
std::set<const CallICFGNode *>& TaintGraphTraversal::identifySinks()
{
    for (const CallICFGNode *cs : pag->getCallSiteSet())
    {
        const SVFFunction *fun = SVFUtil::getCallee(cs->getCallSite());
        if (checker_sink_api.find(fun->getName()) != checker_sink_api.end())
        {
            sinks.insert(cs);
        }
    }
    return sinks;
}

// Start taint checking. 
// There is a tainted flow from p@source to q@sink 
// if (1) alias(p,q)==true and (2) source reaches sink on ICFG.
void TaintGraphTraversal::taintChecking(){
    // configure sources and sinks for taint analysis
    readSrcSnkFromFile("./Assignment-4/SrcSnk.txt");
    ander = new AndersenPTA(pag);
    ander->analyze();
    for(const CallICFGNode* src : identifySources()){
        for(const CallICFGNode* snk : identifySinks()){
            vector<const ICFGNode*> path;
            set<const ICFGNode*> visited;
            std::stack<const SVFInstruction *>callstack;
            if(aliasCheck(src,snk))
                DFS(visited, path, callstack, src, snk);
        }
    }
}

/********************************************************************************************************************
*  Function to print and store paths:
* 
*  This method is called to print each identified path and to store it in a set.
*  Each path is a sequence of node IDs and should be added as a string into std::set<std::string> paths
*  formatted in the form "START: 1->2->4->5->END", where '->' indicates an ICFGEdge connects two ICFGNode IDs.
*
*  Inputs:
*      - std::set<std::string>& paths: Reference to a set to store the formatted paths.
*
*  Outputs:
*      - None directly, but updates the paths set.
********************************************************************************************************************/
void TaintGraphTraversal::printICFGPath(std::vector<const ICFGNode *> &path){
    // Begin the path string with "START: ".
    std::string path_str = "START: ";

    // Loop through the ICFG nodes in the path.
    for (const SVF::ICFGNode *node : path) {
        // Append each node's ID followed by '->' to the path string.
        path_str += to_string(node->getId()) + "->";
    }

    // Finish the path string with "END".
    path_str += "END";
    
    // Insert the path string into the set of paths.
    paths.insert(path_str);
}

/********************************************************************************************************************
*  Function to parse 'SrcSnk.txt' file:
* 
*  This function reads and parses the two lines from `SrcSnk.txt` identifying the sources and sinks.
*  The first line is expected to contain sources and the second line the sinks, each listed within braces.
*  The parsed APIs are to be stored or processed as needed by the program.
*
*  Inputs:
*      - const string& filename: The name of the file to read.
*
*  Outputs:
*      - None directly, but the internal structures are populated with the parsed sources and sinks.
********************************************************************************************************************/
void TaintGraphTraversal::readSrcSnkFromFile(const string& filename) {
    // Open the file.
    std::ifstream file(filename);

    // Variable to hold tokens (words) read from the file one at a time.
    std::string next_token;

    /* Skip over the tokens before the sources list starts. */
    // Read 'source'.
    file >> next_token;

    // Read '->'.
    file >> next_token;

    // Read '{'.
    file >> next_token;

    // Read source APIs from the file until "}" is encountered.
    file >> next_token;
    while (next_token != "}") {
        // Insert the token into the source API set.
        checker_source_api.insert(next_token);

        // Read the next token.
        file >> next_token;
    }

    /* Skip over the tokens before the sinks list starts. */
    // Read 'sink'.
    file >> next_token;

    // Read '->'.
    file >> next_token;

    // Read '{'.
    file >> next_token;

    // Read sink APIs from the file until "}" is encountered.
    file >> next_token;
    while (next_token != "}") {
        // Insert the token into the sink API set.
        checker_sink_api.insert(next_token);

        // Read the next token.
        file >> next_token;
    }

    // Close the file.
    file.close();
}

/********************************************************************************************************************
*  Alias checking function:
* 
*  This function checks for aliasing between the variables at the source and the sink.
*  It returns true if the return value from the source is aliased with any parameter in the sink call.
*  This is determined using an alias analysis mechanism, which may involve the `ander->alias(..,..)` method.
*
*  Inputs:
*      - const CallICFGNode *src: Pointer to the source call node.
*      - const CallICFGNode *snk: Pointer to the sink call node.
*
*  Outputs:
*      - bool: True if there is an alias between source and sink variables, false otherwise.
********************************************************************************************************************/
bool TaintGraphTraversal::aliasCheck(const CallICFGNode *src, const CallICFGNode *snk) {
    // Get the actual return value node from the source.
    auto sourceRetValNode = src->getRetICFGNode()->getActualRet();

    // Get the actual parameters from the sink.
    auto sinkParamNodes = snk->getActualParms();

    // Loop through each parameter in the sink call.
    for (auto sinkParamNode : sinkParamNodes) {
        // Check if the return value from the source is aliased with the sink parameter.
        if (ander->alias(sourceRetValNode->getId(), sinkParamNode->getId())) {
            // Return true if an alias is found.
            return true;
        }
    }

    // Return false if no alias is found.
    return false;
}