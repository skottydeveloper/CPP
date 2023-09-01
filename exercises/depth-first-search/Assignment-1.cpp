/**********************************************************************************************************************
 * NOTE: Code is referenced from the DFS algorithm and examples provided for this assignment, on Canvas.
**********************************************************************************************************************/ 

#include "Assignment-1.h"
using namespace std;

/**********************************************************************************************************************
 *  printPath() function description: 
 *  The 'printPath()' function prints the path from source to destination. An empty path is considered invalid and
 *  won't be printed. The path is formatted as a string with the "START: " prefix and "END" suffix.
 *  Each node ID in the path is separated by an arrow "->". The resulting path string is then printed to the console 
 *  and stored in the paths set.
 *
 *  Inputs:
 *      - std::vector<const Node *> &path: Reference to the vector of nodes that represent the path.
 *
 *  Outputs:
 *      - None, but the path string is printed to the console and stored in the paths set.
 *********************************************************************************************************************/
void GraphTraversal::printPath(std::vector<const Node *> &path) {
    // Check if the path is empty. If so, it's considered invalid and the function returns without printing.
    if (path.empty()) {
        return;
    }

    // Initialise the path string with the "START: " prefix.
    string pathStr = "START: ";

    // Loop through the nodes in the path.
    for (const Node *node : path) {
        // Append the node ID and the arrow "->" to the path string.
        pathStr += to_string(node->getNodeID()) + "->";
    }

    // Append the "END" suffix to the path string.
    pathStr += "END";

    // Print the formatted path string to the console.
    cout << pathStr << endl;

    // Store the path string in the paths set.
    paths.insert(pathStr);
}

/**********************************************************************************************************************
 *  DFS() function description: 
 *  The 'DFS()' function uses Depth First Search to find all paths from source to destination in the graph. 
 *  It starts from the source node and explores as far as possible along each branch before backtracking. 
 *  Each path from source to destination found is then printed using the printPath() function.
 *  Paths cannot be constructed if either the source or destination nodes are null, hence the function exits early
 *  in such cases.
 *
 *  Inputs:
 *      - set<const Node *> &visited: Reference to a set of visited nodes.
 *      - vector<const Node *> &path: Reference to the current path being explored.
 *      - const Node *src: Pointer to the source node.
 *      - const Node *dst: Pointer to the destination node.
 *
 *  Outputs:
 *      - None, but all possible paths from source to destination in the graph are printed to the console using the 
 *        printPath() function.
 *********************************************************************************************************************/
void GraphTraversal::DFS(set<const Node *> &visited, vector<const Node *> &path, const Node *src, const Node *dst) {
    // Exit the function if either the source or destination is null, as paths cannot be constructed with null nodes.
    if (src == nullptr || dst == nullptr) {
        return;
    }

    // Add the current source node to the path vector.
    path.push_back(src);

    // Mark the current source node as visited by adding it to the visited set.
    visited.insert(src);

    // Check if the current source node is the destination node.
    if (src == dst) {
        // If yes, then print the current path using the printPath function.
        printPath(path);
    } else {
        /* If not, then continue the DFS exploration by visiting the neighboring nodes. */

        // Loop through the outgoing edges from the current source node.
        for (const Edge *edge : src->getOutEdges()) {
            // Get the destination node of the current edge.
            Node *neighbour = edge->getDst();

            // Check if the neighbor node has not been visited yet.
            if (visited.find(neighbour) == visited.end()) {
                // If not, then continue the DFS exploration from the neighbor node.
                DFS(visited, path, neighbour, dst);
            }
        }
    }

    /* Once all paths from the current source node have been explored, backtrack. */

    // Remove the current source node from the path vector.
    path.pop_back();

    // Mark the current source node as unvisited by removing it from the visited set.
    visited.erase(src);
}