#include <iostream>

using namespace std;


class A {
	public:
	void print() {
		cout << "In A" << endl;
	}
	virtual void print_virtual() {
		cout << "In A virtual" << endl;
	}
};

class B : public A {
	public:
	void print() {
		cout << "In B" << endl;
	}
	void print_virtual() {
		cout << "In B virtual" << endl;
	}
};

int main(int argc, char *argv[]) {
	A* b = new B();
	b -> print();
	b -> print_virtual();
}
