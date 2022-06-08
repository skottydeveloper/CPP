#include <iostream>
#include <vector>
#include <set>

class Graph {
private:
    std::vector<std::set<unsigned> > vec {};
    unsigned num_vertices = 0;
    std::vector<bool> marked {};
    // Vector of sets to hold the connected components.
    std::vector<std::set<unsigned> > components {};

public:
    Graph(unsigned N) {
        num_vertices = N;
        vec.resize(N);
        marked.resize(N);
    }

    void add_edge(unsigned i, unsigned j) {
        vec[i].insert(j);
        vec[j].insert(i);
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

    void connected_components() {
        for (unsigned v = 0; v < num_vertices; ++v) {
            if (!marked[v]) {
                // Add new set to hold next connected component.
                components.push_back(std::set<unsigned> {}); 
                dfs(v);
            }
        }

        std::cout << "number of components is " << components.size() << '\n';
        unsigned comp_num = 1;
        
        for (const auto& component : components) {
            std::cout << "vertices in component " << comp_num << " are\n";
            
            for (auto v : component) {
                std::cout << v << ' ';
            }

            ++comp_num;
            std::cout << '\n';
        }
    }

private:
   void dfs(unsigned v) {
        marked[v] = true;
        components.back().insert(v);
        
        for (auto u : vec[v]) {
            if (!marked[u]) {
                dfs(u);
            }
        }
    } 
};

int main() {
    // Create a connected undirected graph on 5 vertices.
    Graph G(5);
    G.add_edge(1, 0);
    G.add_edge(0, 3);
    G.add_edge(2, 1);
    G.add_edge(2, 3);
    G.add_edge(3, 1);
    G.add_edge(2, 4);

    // This graph has one component with all the vertices.
    G.connected_components();

    // Create a disconnected undirected graph on 6 vertices.
    Graph G2(6);
    G2.add_edge(0, 4);
    G2.add_edge(0, 5);
    G2.add_edge(4, 5);
    G2.add_edge(1, 3);
    G2.add_edge(1, 2);
    G2.add_edge(2, 3);

    // This graph has two connected components: one with vertices 0 4 5 and the second with vertices 1 2 3.
    G2.connected_components();

    // Create a disconnected undirected graph on 7 vertices.
    Graph G3(7);
    G3.add_edge(0, 1);
    G3.add_edge(0, 6);
    G3.add_edge(2, 5);
    G3.add_edge(3, 4);

    // This graph has three connected components: one with vertices 0 1 6, one with 2 5, one with 3 4.
    G3.connected_components();

    return 0;
}