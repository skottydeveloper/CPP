#include <iostream>
#include <forward_list>
#include <queue>
#include <algorithm>
#include <utility>

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

    // Define a ">" operator for our Edge class.
    bool operator > (const Edge& e) const {
        return (weight > e.weight);
    }    

    void print() const {
        std::cout << '{' << vertex1 << ',' << vertex2;
        std::cout << "}[" << weight << ']';
    }
};

template <int N>
class Graph {
    std::forward_list<Edge> arr[N] {};

public:
    Graph(){}

    Graph(const std::initializer_list<Edge>& input_edges) {
        for (const Edge& e : input_edges) {
            add_edge(e);
        }
    }

    void add_edge(const Edge& e) {
        arr[e.vertex1].push_front(e);
        arr[e.vertex2].push_front(e);
    }

    Graph prim() {
        Graph<N> mst;
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edge_queue {};
        // Start at vertex 0:
        for (const auto& e : arr[0]) {
            edge_queue.push(e);
        }

        bool marked[N] {};
        marked[0] = true;
        
        while (!edge_queue.empty()) {
            Edge min_wt_edge = edge_queue.top();
            edge_queue.pop();
            
            // Check if edge crosses the marked/unmarked cut.
            if (marked[min_wt_edge.vertex1] != marked[min_wt_edge.vertex2]) {
                mst.add_edge(min_wt_edge);
                
                // Identify new vertex to mark.
                int vertex_to_add = !marked[min_wt_edge.vertex1] ? min_wt_edge.vertex1 : min_wt_edge.vertex2;
                
                marked[vertex_to_add] = true;
                
                // Add cut edges of new vertex to the priority queue.
                for (const auto& e: arr[vertex_to_add]) {
                    // Only add edge if it is in the current cut.
                    if (marked[e.vertex1] != marked[e.vertex2]) {
                        edge_queue.push(e);
                    }
                }
            }
        }

        return mst;
    }

    // Compute the sum of the weight of all edges in the graph.
    double total_edge_weight() {
        double total = 0;

        for (int i = 0; i < N; ++i) {
            for (const auto& e : arr[i]) {
                total += e.weight;
            }
        }

        return total / 2;
    }
    
    // Print out the adjacency lists.
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
    Graph mst = G.prim();
    std::cout << "Minimum spanning tree is:\n";
    
    mst.print();
    
    std::cout << "Total weight is " << mst.total_edge_weight() << '\n';
    std::cout << '\n';

    Graph<8> G2 {{4, 5, 0.35}, {4, 7, 0.37}, {5, 7, 0.28}, {0, 7, 0.16}, {1, 5, 0.32}, {0, 4, 0.38}, {2, 3, 0.17}, {1, 7, 0.19}, 
    {0, 2, 0.26}, {1, 2, 0.36}, {1, 3, 0.29}, {2, 7, 0.34}, {6, 2, 0.40}, {3, 6, 0.52}, {6, 0, 0.58}, {6, 4, 0.93}};
    
    Graph mst2 = G2.prim();
    std::cout << "Minimum spanning tree is:\n";
    
    mst2.print();
    std::cout << "Total weight is " << mst2.total_edge_weight() << '\n';
}