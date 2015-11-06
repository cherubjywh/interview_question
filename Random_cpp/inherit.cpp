#include <iostream>

using namespace std;


class A {
	public:
	private:
		void print_private() {
			cout << "A private" << endl;
		}

	protected:
		void print_protected() {
			cout << "A protected" << endl;
		}
};

class B : public A {
	public:
		void print_public_protected() {
			print_protected();
		}
		// The following code will cause problem in compile time
		/*
		void print_public_private() {
			print_private();
		}
		*/
};

int main(int argc, char *argv[]) {
	B b;

	b.print_public_protected();
	// The following code will cause error in compile time
	/*
	b.print_public_private();
	*/
}
