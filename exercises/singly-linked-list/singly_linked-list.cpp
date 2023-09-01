#include <iostream>
using namespace std;

class Node {
    public:
        int data; // the data stored in this node
        Node* next; // pointer to the next node so that nodes can be linked up
};

class LinkedList {
    public:
        int length; // length of the list
        Node* head; // pointer to the first element (node) of the list

        LinkedList(); // constructor is called when a class object is created
        ~LinkedList(); // destructor is called when a class object is deleted
    
        void prepend(int data); // add a new node (containing the input data) to the front of the list
        void append(int data); // add a new node (containing the input data) to the end of the list
        void display(); // show all the data contained in (all the nodes of) the list    
};

LinkedList::LinkedList() {
    this->length = 0; // initialise list length to zero
    this->head = nullptr; // initially, the list is empty upon creation
}

LinkedList::~LinkedList() {
    while(this->head != nullptr) {
        Node* temp = this->head; // find the location of the current node
        this->head = this->head->next; // traverse the nodes in the list one by one
        delete temp; // deallocate space occupied by the current node
    }
    cout << "Linked list deleted!" << endl;
}

void LinkedList::prepend(int data) {
    // Step 1: create a new node dynamically (using pointer)
    Node* new_node = new Node();
    new_node -> data = data;
    
    // Step 2: add to new node to the list, make the new node point to the previous first node and the new node will become the first node of the list
    new_node -> next = this -> head;
    this -> head = new_node; 

    // Step 3: increase the length of list by 1
    this->length++;  
}

void LinkedList::append(int data) {
    // Step 1: create a new node dynamically (using pointer)
    Node* new_node = new Node();
    new_node->data = data;
    new_node->next = nullptr;

    // Step 2: add the new node to the list first, find the last node of the list. Then, let the last node point to the new node.
    Node* ptr = this->head;
    
    while (ptr->next) {
        ptr = ptr->next;
    }

    ptr->next = new_node;

    // Step 3: increase the length of list by 1
    this->length++;  
}   

void LinkedList::display() {
    // get a pointer that points to the first node of the list
    Node* temp = this -> head;

    // track the nodes forward one by one using the pointer in each node - only the pointer in the last node is nullptr.
    while (temp != nullptr) {
        cout << temp -> data << "\n";
        temp = temp -> next;
    }
}

int main() {
    // declare a pointer (an empty linkedlist)
    LinkedList* list = new LinkedList();
    
    // add three nodes to the front
    list->prepend(1);
    list->prepend(3);
    list->prepend(5);
    
    // add three nodes to the end
    list->append(2);
    list->append(4);
    list->append(6);

    // print list elements and length
    list->display();
    cout << "List Length: " << list->length << endl;

    // remove linkedlist from memory space
    delete list;
}