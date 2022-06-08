#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>

class Graph {
private:
    std::vector<std::set<unsigned>> vec {};
    unsigned num_vertices = 0;
    bool is_directed = 0;

public:
    Graph(unsigned N, bool type) {
        num_vertices = N;
        is_directed = type;
        vec.resize(N);
    }

    void add_edge(unsigned i, unsigned j) {
        vec[i].insert(j);

        if (!is_directed) {
            vec[j].insert(i);
        }
    }

    bool is_edge(unsigned i, unsigned j) {
        return vec[i].contains(j);
    }

    void adj_to_v(unsigned v) {
        for (auto x : vec[v]) {
            std::cout << x << ' ';
        }

        std::cout << '\n';
    }

    void print() {
        for (unsigned v = 0; v < num_vertices; ++v) {
            std::cout << "Neighbors of " << v << ": ";

            for (auto nbh : vec[v]) {
                std::cout << nbh << ' ';
            }

            std::cout << '\n';
        }
    }
};

int main() {
    // Create an undirected graph on five vertices.
    Graph G(5, false);
    G.add_edge(1, 0);
    G.add_edge(0, 3);
    G.add_edge(2, 1);
    G.add_edge(2, 3);
    G.add_edge(3, 1);
    G.add_edge(2, 4);

    // Print out all the edges: {0,1}, {0,3}, {1,2}, {1,3}, {2,3}, {2,4}
    G.print();

    // Print out vertices adjacent to vertex 2.
    G.adj_to_v(2);

    std::cout << "Directed graph:\n";
    // Create a directed graph on 4 vertices.
    Graph digraph(4, true);
    digraph.add_edge(1,0);
    digraph.add_edge(0,3);
    digraph.add_edge(2,1);
    digraph.add_edge(2,3);
    digraph.add_edge(3,1);

    // Print out all the edges: (0,3), (1,0), (2,1), (2,3), (3,1)
    digraph.print(); 

    // Print out the vertices out-adjacent to vertex 0.
    digraph.adj_to_v(0);

    return 0;
}