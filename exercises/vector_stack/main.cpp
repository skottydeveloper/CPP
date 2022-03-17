#include <iostream>
#include "stack.hpp"

int main() {
	Stack<int> s;               // Create a stack.
	const int add_num = 2;     // The number of elements to be added to stack.
	const int remove_num = 5;   // The number of elements to be removed from stack.

	/* Add things to stack. */
	for (int i = 0; i < add_num; i++) {
		s.push(i);
	}

	/* Remove things from stack. */
	int count = 0;              // Count the elements that have been removed. 
	
	while (count < remove_num) {
		s.pop();
		count++;
	}

	/* Check what is left in the stack. */
	while (!s.empty()) {
		cout << s.top() << endl;
		s.pop();
	}
}