#include <iostream>
using namespace std;

long recursive_fibonacci(long n) {
	if (n <= 1) {
		return n;
	}
    return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
}

int iterative_fibonacci(int n) {
	int a = 0, b = 1, c, i;

    if (n == 0) {
		return a;
	}
        
    for (i = 2; i <= n; i++) {
       c = a + b;
       a = b;
       b = c;
    }
    return b;
}

int main() {
	int n;

	cout << "Enter a number:" << endl;
	cin >> n;

	cout << "The nth Fibonacci number is: " << recursive_fibonacci(n) << endl;
	cout << "The nth Fibonacci number is: " << iterative_fibonacci(n) << endl;	
}