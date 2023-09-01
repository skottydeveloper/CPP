//===- Software-Analysis-Teaching Assignment
// 1-------------------------------------//
//
//     SVF: Static Value-Flow Analysis Framework for Source Code
//
// Copyright (C) <2013->
//

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//===-----------------------------------------------------------------------===//

/*
 // Software-Analysis-Teaching Assignment 1 : Graph Traversal
 //
 //
 */

#include "Assignment-1.h"
#include <assert.h>

void Test1() {
    /*


        1
       /  \
      2   3
       \ /
        4
        |
        5

  */
    // init nodes
    Node *node1 = new Node(1);
    Node *node2 = new Node(2);
    Node *node3 = new Node(3);
    Node *node4 = new Node(4);
    Node *node5 = new Node(5);

    // init edges
    Edge *edge1 = new Edge(node1, node2);
    Edge *edge2 = new Edge(node1, node3);
    node1->addOutEdge(edge1);
    node1->addOutEdge(edge2);
    Edge *edge3 = new Edge(node2, node4);
    Edge *edge4 = new Edge(node3, node4);
    node2->addOutEdge(edge3);
    node3->addOutEdge(edge4);
    Edge *edge5 = new Edge(node4, node5);
    node4->addOutEdge(edge5);

    // init Graph
    Graph *g = new Graph();
    g->addNode(node1);
    g->addNode(node2);
    g->addNode(node3);
    g->addNode(node4);
    g->addNode(node5);
    // test
    std::set<std::string> expected_answer{"START: 1->2->4->5->END",
                                          "START: 1->3->4->5->END"};
    std::set<const Node *> visited;
    std::vector<const Node *> path;
    GraphTraversal *dfs = new GraphTraversal();
    dfs->DFS(visited, path, node1, node5);
    assert(dfs->getPaths() == expected_answer && "Test case 1 failed!");
    std::cout << "Test case 1 passed!\n";
}

void Test2() {
    /*

        1
        |
        2
        |
        3
        |
        4

     */
    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);
    Node *n4 = new Node(4);

    Edge *e12 = new Edge(n1, n2);
    n1->addOutEdge(e12);
    Edge *e23 = new Edge(n2, n3);
    n2->addOutEdge(e23);
    Edge *e34 = new Edge(n3, n4);
    n3->addOutEdge(e34);

    Graph *g = new Graph();
    g->addNode(n1);
    g->addNode(n2);
    g->addNode(n3);
    g->addNode(n4);

    std::set<std::string> expected_answer{"START: 1->2->3->4->END"};

    std::set<const Node *> visited;
    std::vector<const Node *> path;
    GraphTraversal *dfs = new GraphTraversal();
    dfs->DFS(visited, path, n1, n4);
    assert(dfs->getPaths() == expected_answer && "Test case 2 failed!");
    std::cout << "Test case 2 passed!\n";
}

void Test3() {
    /*

        1
      /   \
     2     3
    | \   / \
   4    5    6
    \  / \  /
     7    8
      \  /
       9

     */
    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);
    Node *n4 = new Node(4);
    Node *n5 = new Node(5);
    Node *n6 = new Node(6);
    Node *n7 = new Node(7);
    Node *n8 = new Node(8);
    Node *n9 = new Node(9);

    Edge *e12 = new Edge(n1, n2);
    Edge *e13 = new Edge(n1, n3);
    n1->addOutEdge(e12);
    n1->addOutEdge(e13);

    Edge *e24 = new Edge(n2, n4);
    Edge *e25 = new Edge(n2, n5);
    n2->addOutEdge(e24);
    n2->addOutEdge(e25);

    Edge *e35 = new Edge(n3, n5);
    Edge *e36 = new Edge(n3, n6);
    n3->addOutEdge(e35);
    n3->addOutEdge(e36);

    Edge *e47 = new Edge(n4, n7);
    n4->addOutEdge(e47);

    Edge *e57 = new Edge(n5, n7);
    Edge *e58 = new Edge(n5, n8);
    n5->addOutEdge(e57);
    n5->addOutEdge(e58);

    Edge *e68 = new Edge(n6, n8);
    n6->addOutEdge(e68);

    Edge *e79 = new Edge(n7, n9);
    n7->addOutEdge(e79);

    Edge *e89 = new Edge(n8, n9);
    n8->addOutEdge(e89);

    std::set<std::string> expected_answer{
        "START: 1->3->5->7->9->END", "START: 1->3->5->8->9->END",
        "START: 1->3->6->8->9->END", "START: 1->2->4->7->9->END",
        "START: 1->2->5->7->9->END", "START: 1->2->5->8->9->END",
    };

    std::set<const Node *> visited;
    std::vector<const Node *> path;
    GraphTraversal *dfs = new GraphTraversal();
    dfs->DFS(visited, path, n1, n9);
    assert(dfs->getPaths() == expected_answer && "Test case 3 failed!");
    std::cout << "Test case 3 passed!\n";
}

void Test4() {
    /*

        1
        |
        2
        |
        3

        4

     */
    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);
    Node *n4 = new Node(4);

    Edge *e12 = new Edge(n1, n2);
    n1->addOutEdge(e12);
    Edge *e23 = new Edge(n2, n3);
    n2->addOutEdge(e23);

    Graph *g = new Graph();
    g->addNode(n1);
    g->addNode(n2);
    g->addNode(n3);
    g->addNode(n4);

    std::set<std::string> expected_answer{};

    std::set<const Node *> visited;
    std::vector<const Node *> path;
    GraphTraversal *dfs = new GraphTraversal();
    dfs->DFS(visited, path, n1, n4);
    assert(dfs->getPaths() == expected_answer && "Test case 4 failed!");
    std::cout << "Test case 4 passed!\n";
}

/// Entry of the program
int main() {
    Test1();
    Test2();
    Test3();
    Test4();
    return 0;
}