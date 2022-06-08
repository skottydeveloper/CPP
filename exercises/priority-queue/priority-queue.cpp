#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>

// This is the "Edge" class we will use in our minimum spanning tree program.
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
    bool operator <(const Edge& e) const {
        return (weight < e.weight);
    }

    // Define a ">" operator for our Edge class.
    bool operator >(const Edge& e) const {
        return (weight > e.weight);
    }    

    void print() const {
        std::cout << '{' << vertex1 << ',' << vertex2;
        std::cout << "}[" << weight << ']';
    }
};

int main() {
    // Does this define a min priority queue or a max priority queue? Push some elements to it and use the top to find out.
    std::priority_queue<int> q1;
    q1.push(3);
    q1.push(7);
    q1.push(-1);
    std::cout << "Example 1: top value is ";
    std::cout << q1.top() << '\n';
    /* This is a max priority queue. A priority queue can accept 3 template arguments:  
        1) The first is the type of objects in the queue. Here we will again construct a priority queue of ints.
        2) The second specifies what kind of underlying container to use for the priority queue. We will use a std::vector<int>.  
        3) The third argument is a comparison function. The default here is less than. 
        By instead using greater than we can switch from a max priority queue to a min priority queue. */
    
    // Test that this is indeed a min priority queue now. 
    std::priority_queue<int, std::vector<int>, std::greater<int>> q2;
    q2.push(3);
    q2.push(7);
    q2.push(-1);
    std::cout << "example 2: top value is ";
    std::cout << q2.top() << '\n';

    /* Now it is a min priority queue. For the application to minimum spanning trees we will have a minimum priority queue of edges, 
    where edges are compared by their edge weight. */   
    
    /* Just as in the priority queue of ints example, to get a min priority queue we want to compare with a greater than function.
    This time we want to use the operator ">" we have defined in the Edge class. 
    We can set up a priority queue of Edges with this comparison function like this: */
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edge_queue;

    // Using the queue now:
    
    // Add an edge between vertex 0 and vertex 1 of weight 0.5.
    edge_queue.push({0, 1, 0.5});

    // Add an edge between vertex 1 and vertex 3 of weight 2.7.
    edge_queue.push({1, 3, 2.7});

    // Add an edge between vertex 1 and vertex 2 of weight 1.1. 
    edge_queue.push({1, 2, 1.1});

    // What is the minimum weight edge in the queue now?
    Edge e = edge_queue.top();

    std::cout << "Minimum weight of edge is ";
    std::cout << e.weight << '\n';

    return 0;
}