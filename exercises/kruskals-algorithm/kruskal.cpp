#include <iostream>
#include <forward_list>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

class Edge {   
public:
    int vertex1;
    int vertex2; 
    double weight;
    
    Edge(int v1, int v2, double w) {  
        vertex1 = v1; 
        vertex2 = v2;
        weight = w;
    }

    // Define a "<" operator for our Edge class.
    bool operator < (const Edge& e) const {
        return (weight < e.weight);
    }

    // Define a ">" operator for our Edge class. Kept here for the sake of consistency.
    bool operator>(const Edge& e) const {
        return (weight > e.weight);
    }    

    void print() const {
        std::cout << '{' << vertex1 << ',' << vertex2;
        std::cout << "}[" << weight << ']';
    }
};

template <int N>
class Union_find {
private:
    // If "x" is the root of its tree then "id_arr[x] == x", otherwise "id_arr[x]" will be the parent of "x" in the tree containing "x".
    int id_arr[N];
    // "sizes[find(i)]" will be the size of the set containing "i".
    int sizes[N];

public:
     // Initialise every element in its own set.
    Union_find() {
        for (int i = 0; i < N; ++i) {
            id_arr[i] = i;
            sizes[i] = 1;
        }
    }

    // Return the name of the root of the tree containing element.
    int find(int element) {
        while (element != id_arr[element]) {
            element = id_arr[element];
        }

        return element;
    }

    // Are "element1" and "element2" in the same set?
    bool same_set(int element1, int element2) {
        return find(element1) == find(element2);
    }

    // Merge the sets containing "element1" and "element2".
    void merge(int element1, int element2) {
        int root1 = find(element1);
        int root2 = find(element2);

        if (root1 == root2) {
            return;
        }

        if (sizes[root1] < sizes[root2]) {
            id_arr[root1] = root2;
            sizes[root2] += sizes[root1];
        } else {
            id_arr[root2] = root1;
            sizes[root1] += sizes[root2];
        }
    }
    
    // Print out the set id of each element to help in debugging.
    void print() {
        for (int i = 0; i < N; ++i) {
            std::cout << i << " is in set " << find(i) << '\n';
        }
    }
};

template <int N>
class Graph {
    std::forward_list<Edge> arr[N] {};

public:
    Graph() {}

    // Constructor from "initializer_list".
    Graph(const std::initializer_list<Edge>& input_edges) {
        for (const Edge& e : input_edges) {
            add_edge(e);
        }
    }

    void add_edge(const Edge& e) {
        arr[e.vertex1].push_front(e);
        arr[e.vertex2].push_front(e);
    }

    // Make a vector containing all edges in the graph.
    std::vector<Edge> all_edges() {
        std::vector<Edge> edge_vec;

        for (int i = 0; i < N; ++i) {
            for (const auto& e : arr[i]) {
                // We want each edge just once.
                if (e.vertex1 == i) {
                    edge_vec.push_back(e);
                }
            }
        }

        return edge_vec;
    }

    // Use Kruskal's algorithm to return a minimum spanning tree. 
    Graph kruskal() {
        std::vector<Edge> edge_vec = all_edges();
        // "sort" will automatically use operator "<"" from our Edge class.
        std::sort(edge_vec.begin(), edge_vec.end());
        Graph<N> mst;
        Union_find<N> forest_components;

        for (const auto& e : edge_vec) {
            int v1 = e.vertex1;
            int v2 = e.vertex2;
            
            if (!forest_components.same_set(v1, v2)) {
                mst.add_edge(e);
                forest_components.merge(v1, v2);
            }
        }

        return mst;
    }

    // Output the sum of all edge weights in the graph.
    double total_edge_weight() {
        double total = 0;

        for (int i = 0; i < N; ++i) {
            for (const auto& e : arr[i]) {
                total += e.weight;
            }
        }

        return total / 2;
    }
    
    // Print out the graph.
    void print() {
        for (int i = 0; i < N; ++i) {
            std::cout << "Neighbors of " << i << ": ";

            for (const auto& e : arr[i]) {
                e.print();
                std::cout << ' ';
            }

            std::cout << '\n';
        }
    }
};

int main() {
    Graph<7> G {{0, 1, 2600}, {0, 2, 3600}, {1, 3, 2800}, {1, 5, 3000}, {2, 3, 1400}, {2, 4, 1900}, {3, 4, 900}, {4, 5, 880}, {4, 6, 1000}, {5, 6, 700}};
    Graph mst = G.kruskal();
    std::cout << "Minimum spanning tree is:\n";
    
    mst.print();

    std::cout << "Total weight is " << mst.total_edge_weight() << '\n';
    std::cout << '\n';

    Graph<8> G2 {{4, 5, 0.35}, {4, 7, 0.37}, {5, 7, 0.28}, {0, 7, 0.16}, {1, 5, 0.32}, {0, 4, 0.38}, {2, 3, 0.17}, 
    {1, 7, 0.19}, {0, 2, 0.26}, {1, 2, 0.36}, {1, 3, 0.29}, {2, 7, 0.34}, {6, 2, 0.40}, {3, 6, 0.52}, {6, 0, 0.58}, {6, 4, 0.93}};
    Graph mst2 = G2.kruskal();
    std::cout << "Minimum spanning tree is:\n";
    
    mst2.print();
    std::cout << "Total weight is " << mst2.total_edge_weight() << '\n';

    return 0;
}