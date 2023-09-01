#ifndef OURSTACK_HPP_ // Header guard to avoid re-declaring a class twice.
#define OURSTACK_HPP_

class OurStack {
  private:
    /* private classes */
    class Node {
      public:
        int data;
        Node * next;
        
        Node(int data, Node * next); // Constructor for Node.
        ~Node();         // Destructor for Node.
    };

    /* Private attributes. */
    Node * head;
    size_t length;

  public:
    /* Public methods. */
    OurStack();          // Constructor for OurStack.
    ~OurStack();         // Destructor for OurStack.
  
    bool empty();        // Check whether stack is empty.
    size_t size();       // Gets stack size.
    int top();           // Get the top element.
    void push(int data); // Add an element (to the top).
    void pop();          // Remove an element (from the top).
};

#endif