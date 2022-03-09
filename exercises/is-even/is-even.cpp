#include <iostream>
#include "is-even.hpp"

IsEven::IsEven() {
	
};

IsEven::IsEven(int n) { 
	myNum = n;
}; 

int IsEven::get_value() {
	return myNum;
}

void IsEven::set_value(int n) {
	myNum = n;
}

int IsEven::sum_up(int n) {
	return n + myNum;
}

bool IsEven::is_even() {
	return myNum % 2 == 0;
}

int main() { 
	int a = 5, b = 10;

	IsEven * ptr = new IsEven(a);
	std::cout << "Is " << a << " even? " << ptr->is_even() << std::endl;

	IsEven obj;
	obj.set_value(b);
	std::cout << "Is " << b << " even? " << obj.is_even() << std::endl;

	std::cout << "The sum of a and b is " << ptr->sum_up(obj.get_value()) << std::endl;

	delete ptr;
}