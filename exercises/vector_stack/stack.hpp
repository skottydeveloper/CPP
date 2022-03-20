#ifndef STACK
#define STACK

#include <vector>
using namespace std;

template <typename T>

class Stack {
	private:
		vector<T> data; // The underlying data structure for the stack is a vector.
	
	public:
		Stack(){}       // Constructor (empty).
		~Stack(){}      // Destructor (empty).
		
		/* Add an element to the top of stack (i.e., back of vector). */
		void push (T t) {
			data.push_back(t); 
		}
		
		/* Remove an element from the top of stack (i.e., back of vector). */
		void pop() {
			data.pop_back();
		}
		
		/* Get the element at the top of stack (i.e., back of vector). */
		T top() {
			return data.back();
		}
		
		/* Check if the stack is empty. */
		bool empty() {
			return data.empty();
		}
};

#endif