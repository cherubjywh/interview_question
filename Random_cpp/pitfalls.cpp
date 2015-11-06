#include<iostream>
#include<string>

using namespace std;

void pitfall_constructor_1() {
	// A declaration of a function
	// The stupid thing is useless at all
	// It is called "declaring a function in a local scope"
	string b();
	string c;

	
	/*
	   // identified to be a pitfall
	   
	cout << "b size " << b.size() << endl;
	*/
	cout << "c size " << c.size() << endl;
}

template<typename T>
class Array {
	public:
		Array(int s):size(s) {cout << "in int constructor\n";}
		Array(double s):size((int)s) {cout << "in double constructor\n";}
		int size;
};

template<typename T>
class Brray {
	public:
		explicit Brray(int s):size(s){cout << "in int constructor\n";}
		int size;
};

void pitfall_constructor_2() {
	Array<int> a(32);
	// Constructors with one argument sever double duty as type conversions
	Array<int> b = 32;
	Array<int> c = 32.0;
	// The previous two examples coulde explain what is double duty in this case
	// Lesson: Avoid constructors with a single integer argument! Use the explicit keyword if you cannot avoid them

	cout << "a: " << a.size << endl;
	cout << "b: " << b.size << endl;
	cout << "c: " << c.size << endl;

	/*

	// Try to call as converting constructor, but it does not work this case because of explict keyword
	 Brray<int> d = 32;
	 */

	Brray<int> e(32);
}

int main(int argc, char* argv[]) {

	// pitfall_constructor_1();
	pitfall_constructor_2();

}
