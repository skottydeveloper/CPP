/******************************************************************************************************************************************************************************************
 * NOTE: Code is referenced from the algorithm and examples provided for this assignment, on Canvas.
******************************************************************************************************************************************************************************************/

#include <set>
#include "Assignment-2.h"
#include <iostream>
using namespace SVF;
using namespace std;

/******************************************************************************************************************************************************************************************
 * printICFGPath() function description: 
 * This function prints the path of ICFGNodes and subsequently adds each path into a set. The path is presented in a specific format: "START: 1->2->4->5->END", where "->" serves as an 
 * indication that an ICFGEdge connects two sequential ICFGNode IDs.
 *
 * Inputs:
 * - A 'std::vector<const ICFGNode *>' which points towards the path that is intended to be printed.
 *
 * Outputs:
 * - The function does not return any values. Instead, it prints the path and ensures that the printed path is added to the 'paths' set.
 *****************************************************************************************************************************************************************************************/
void ICFGTraversal::printICFGPath(std::vector<const ICFGNode *> &path) {
    // Return if the path is empty.
    if (path.empty()) {
        return;
    }
    
    string strPath = "START: ";
    
    // Loop through each ICFGNode in the path.
    for (size_t i = 0; i < path.size(); i++) {
        // Add the ID of the ICFGNode to the path string.
        strPath += to_string(path[i]->getId());

        // Add "->" to the path string if the current ICFGNode isn't the last in the path.
        if (i != path.size() - 1) {
            strPath += "->";
        } 
    }

    // Append "END" to the path string.
    strPath += "->END";

    // Print the path.
    cout << strPath << endl;
    
    // Insert the path into the paths set.
    paths.insert(strPath);
}

/******************************************************************************************************************************************************************************************
 * DFS() function description: 
 * This function implements a depth-first search (DFS) traversal on the ICFG. Its primary objective is to identify and traverse all possible paths that extend from a 
 * source (src) node, finishing at a destination (dst) node. Uniquely, this traversal is context-sensitive. This means that it respects, acknowledges, and follows the 
 * intricate call-return structure that is common in the program it's analysing.
 *
 * Inputs:
 * - 'std::set<const ICFGNode *>': This is a set of nodes that have been visited during the DFS traversal.
 * - 'std::vector<const ICFGNode *>': A vector that holds the path of nodes being explored.
 * - 'std::stack<const SVFInstruction*>': This stack aids in the context-sensitive traversal by keeping track of call sites.
 * - 'const ICFGNode *': A pointer that points to the source node from where the DFS traversal commences.
 * - 'const ICFGNode *': A pointer to the intended destination node, where the traversal aims to reach.
 *
 * Outputs:
 * - This function does not have any direct outputs in the form of return values. However, during its execution, it employs the 'printICFGPath' function to print identified paths and to 
 * efficiently manage the contents of the 'paths' set.
 *****************************************************************************************************************************************************************************************/
void ICFGTraversal::DFS(std::set<const ICFGNode *> &visited, std::vector<const ICFGNode *> &path, std::stack<const SVFInstruction*> &callstack, const ICFGNode *src, const ICFGNode *dst) {
    // Mark the source node as visited and add it to the current path.
    visited.insert(src);
    path.push_back(src);

    // If the source node is the destination, print the path.
    if (src == dst) {
        printICFGPath(path);
    } else {
        // Explore all outgoing edges from the source node.
        for (const ICFGEdge* e : src->getOutEdges()) {
            const ICFGNode* dstNode = e->getDstNode();
            
            // Continue if the destination node has not been visited.
            if (visited.find(dstNode) == visited.end()) {
                // If the edge is an intra-procedural edge, continue the DFS traversal.
                if (e->isIntraCFGEdge()) {
                    DFS(visited, path, callstack, dstNode, dst);
                // If the edge is a call edge in the ICFG, push the call site onto the callstack and continue traversal.
                } else if (e->isCallCFGEdge()) {
                    // Cast the source node to a CallICFGNode to access call site information.
                    const CallICFGNode* callEdge = SVFUtil::dyn_cast<CallICFGNode>(src);
                    
                    if (callEdge) {
                        // Push the call site of the edge to the call stack.
                        callstack.push(callEdge->getCallSite());

                        // Continue DFS from the destination node of the current edge.
                        DFS(visited, path, callstack, dstNode, dst);
                    }
                // If the edge is a return edge in the ICFG, ensure it matches the top of the callstack (if not empty) before popping it and continuing traversal.
                } else if (e->isRetCFGEdge()) {
                    // Cast the source node to a RetICFGNode to access call site information.
                    const RetICFGNode* retNode = SVFUtil::cast<RetICFGNode>(src);
                    
                    // Ensure the call stack is not empty and the top of the stack matches the call site of the edge.
                    if (retNode && !callstack.empty() && callstack.top() == retNode->getCallSite()) {
                        // Pop the call site from the call stack.
                        callstack.pop();

                        // Continue DFS from the destination node of the current edge.
                        DFS(visited, path, callstack, dstNode, dst);
                    }
                }
            }
        }
    }

    // Backtrack: Remove the source node from the visited set and the current path.
    visited.erase(src);
    path.pop_back();
}