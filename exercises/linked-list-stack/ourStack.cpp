#include <iostream>
#include "ourStack.hpp"
using namespace std;

/* The Node() functions belongs to the Node class, which belongs to the OurStack class */
OurStack::Node::Node(int data, Node * next) {
  this->data = data;
  this->next = next;
}

OurStack::Node::~Node() {}

/* Initialise attributes for the OurStack class */
OurStack::OurStack() {
  this->head = nullptr;
  this->length = 0;
}

/* Free up memory for all Node objects one by one, in OurStack's destructor. */
OurStack::~OurStack() {
  while (this->head != nullptr) {
      Node* temp = this->head;
      this->head = this->head->next;
      delete temp;
  }
}

// Check whether stack is empty.
bool OurStack::empty() {
  return (length == 0);
}

// Get stack size.
size_t OurStack::size() {
  return length;
}

/* The top element of the stack is the first node in the linked list. */
int OurStack::top() { 
  if (this->head != nullptr) {
      return head->data;
  }
  return - 1;
}

/* Add an element to the top of the stack. */
void OurStack::push(int data) {
  cout << "Add " << data << endl;
  ++length;
  head = new Node(data, head);
}

/* Remove an element from the top of the stack. */
void OurStack::pop() { 
  if (this->head != nullptr) {
    cout << "Remove " << this->head->data << endl;
  }
  
  --length;
  Node* tmp = head;
  head = head->next;
  delete tmp;
}

int main() {
  OurStack * st = new OurStack();

  for (int i = 0; i <= 20; i++) {
    st->push(i);       // Add 20 integers to the stack.
    if (i % 3 == 0) {
      st->pop();       // Remove some of the integers.
    }
  }

  cout << endl;
  
  cout << "Current stack size is: " << st->size() << endl;
  cout << "Is current stack empty? " << st->empty() << endl;
  cout << "The top element is: " << st->top() << endl;
  
  delete st;
}