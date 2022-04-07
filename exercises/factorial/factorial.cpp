using namespace std;

unsigned long long iterative_factorial(unsigned long long n) {	
	int res = 1, i;

    for (i = 2; i <= n; i++) {
		res *= i;
	}
    return res;
}

unsigned long long recursive_factorial(unsigned long long n) {
	if (n == 0) {
		return 1;
	}
	return n * recursive_factorial(n - 1);
}

int main() {
	unsigned long long n; // this data type can hold a larger number that the normal int. It can only hold positive values.
	
	cout << "Please input a positive integer (<=65):" << endl;
	cin >> n;
	
	cout << iterative_factorial(n) << endl;
	cout << recursive_factorial(n) << endl;
}