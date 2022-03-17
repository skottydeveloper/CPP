#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void showQueue(queue<int> q) { // show all elements in a queue
	cout << "All elements in Queue:";
	
	while (!q.empty()) {
		cout << " " << q.front(); //show first element of queue
		q.pop();
	}
	
	cout << endl;
}

void showStack(stack<int> s) { // show all elements in a stack
	cout << "All elements in Stack:";
    
	// your code here
	while (!s.empty()) {
    	cout << " " << s.top();
		s.pop();
	}

	cout << endl;
}
 
int main() {
	// do some operations on a queue and see what is left
	queue<int> q;
	q.push(1); 
	q.push(2);
	q.pop(); 
	q.push(3); 
	q.push(4);
	q.pop();
	q.push(5);
	showQueue(q);

	// do some operations on a stack and see what is left
	stack <int> s;
    s.push(1); 
    s.push(2);
	s.pop(); 
    s.push(3);
    s.push(4);
	s.pop();
    s.push(5);
    showStack(s);
}