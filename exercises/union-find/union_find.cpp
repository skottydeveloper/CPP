#include <iostream>
#include <forward_list>
#include <deque>
#include <set>
#include <algorithm>
#include <random>
#include <utility>
#include <cassert>

template <int N>
class Union_find {
private:
    // If "x" is the root of its tree then "id_arr[x] == x", otherwise "id_arr[x]"" will be the parent of "x" in the tree containing "x".
    int id_arr[N];
    // "sizes[find(i)]"" will be the size of the set containing "i".
    int sizes[N];

public:
     // Initialise every element in its own set.
    Union_find() {
        for (int i = 0; i < N; ++i) {
            id_arr[i] = i;
            sizes[i] = 1;
        }
    }

    // Return the set id of element.
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

// We include the graph class here, just to test your union-find data structure.
template <int N>
class Graph {
private:
    std::forward_list<int> adj_list[N];
    bool marked[N] {};

public:
    // Deque of sets to hold the connected components, we make this public for "test_union_find".
    std::deque<std::set<int>> components {};

    Graph() {}

    void add_edge(int i, int j) {
        adj_list[i].push_front(j);
        adj_list[j].push_front(i);
    }

    void print() {
        for (int v = 0; v < N; ++v) {
            std::cout << "Neighbors of " << v << ": ";
            
            for (int nbh : adj_list[v]) {
                std::cout << nbh << ' ';
            }

            std::cout << '\n';
        }
    }

    void connected_components() {
        // "component_num" will label a connected component.
        for (int v = 0; v < N; ++v) {
            if (!marked[v]) {
                // Add new set to hold next connected component.
                components.push_front(std::set<int> {v}); 
                dfs(v);
            }
        }
    }

private:
   void dfs(int v) {
        marked[v] = true;
        components[0].insert(v);

        for (int u : adj_list[v]) {
            if (!marked[u]) {
                dfs(u);
            }
        }
    } 
};

void test_union_find() {
    // Create a graph on "n" nodes with "num_edges" edges.
    const int n = 10;
    const int num_edges = 10;
    Graph<n> G;
    Union_find<n> sets;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> vertex_dist(0,n-1);
    // We add random edges to the graph, and merge the sets containing the endpoints.
    for (int i = 0; i < num_edges; ++i) {
        int v1 = vertex_dist(mt);
        int v2 = vertex_dist(mt);

        if (v1 != v2) {
            G.add_edge(v1,v2);
            sets.merge(v1,v2);
        }
    }
    // Now our union-find data structure should have exactly the connected components of the graph!
    G.connected_components();

    for (const auto& component: G.components) {
        int first = *component.begin();
        int id = sets.find(first);

        for (int x: component) {
           assert(id == sets.find(x)); 
           assert(sets.same_set(first,x)); 
        } 
    }

    std::cout << "test passed\n";
}

int main() {
    Union_find<7> sets;
    sets.merge(5, 6);
    sets.merge(5, 4);
    sets.merge(3, 4);
    sets.merge(2, 3);
    sets.merge(0, 1);
    sets.merge(1, 3);
    // All elements should be in the same set.
    sets.print();

    for (int i = 0; i < 5; ++i) {
        test_union_find();
    }

    return 0;
}