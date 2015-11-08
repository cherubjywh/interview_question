#include<iostream>
#include<string>
#include<cmath>

using namespace std;

void pitfall_constructor_1() {
	// A declaration of a function
	// The stupid thing is useless at all
	// It is called "declaring a function in a local scope"
	// It is interprated as function declaration
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

void pitfall_new_1() {
	// Moral: Array/pointer duality is dumb, but unfortunately pervasive in C and C++
	int * p = new int(10);
	cout << "Pitfall_new_1: " << *p << endl;
	delete p;
}

/*

   // Even compiler is checking and telling me that _capacity is used before it is initialized
   // Sweet that this type of error can be detected nowdays

template<typename T>
class A_init_members {
	public:
		// This is tricky, initialization follows the member declaration order, not the initializer order
		A_init_members(int size):
			_size(size),_capacity(size + 10),_data(new T[_capacity])
		{}

		T operator[] (size_t i) {
			return _data[i];
		}

	private:

		T *_data;
		int _size;
		int _capacity;
};
*/

template<typename T>
class A_init_members_correct {
	public:
		// Tip: Do not use data member in initializer expressions
		A_init_members_correct(int size):
			_size(size), _capacity(size + 10), _data(new T[size + 10])
	{}
	private:

		T *_data;
		int _size;
		int _capacity;
};

void pitfall_constructor_initialize_members() {
//	A_init_members<int> A(10);
	// Should not be OK
//	cout << A[9] << endl;
	
	A_init_members_correct<int> A_correct(10);
}

class Point {
	public:
		// Default arguments can lead to unintended calls. Only use defaults if all resulting call patterns are meaningful
		// e.g. Gaussian noisy is by default white noise, i.e. 0 mean and 1 variance
		Point (double x = 0, double y = 0):_x(x), _y(y) {}
		void print() {cout << "Point.x: " << _x << ", Point.y: " << _y << endl;}
	private:
		double _x, _y;
};


void pitfall_constructor_default_arguments() {
	double a = 10.0, r = 5.0, x = 3.0, y = 1.0;
	Point p = (x + r * cos(a), y + r * sin(a));
	p.print();
	
}

namespace constructor_virtual_function {
	enum Color {
		BLACK,
		RED,
		WHITE
	};

	class Shape {
		public:
			Shape() { reset(); }
			void print_color() {
				switch (_color)  {
				case Color::BLACK:
					cout << "Black\n";
					break;
				case Color::RED:
					cout << "Red\n";
					break;
				case Color::WHITE:
					cout << "White\n";
				}
			}
		private:
			virtual void reset() {_color = Color::BLACK; cout << "Shape\n";}
			Color _color;
	};

	class Point : public Shape {
		public:
		private:
			// void reset() {Shape::reset();}
			void reset() {cout << "Point\n";}
			double _x, _y;
	};
};

void pitfall_constructor_virtual_function () {
	// reset of Shape is called rather than reset of Point
	constructor_virtual_function::Point p;
	p.print_color();
}

namespace test_constructor {
	class Shape {
		public:
			Shape() {cout << "In Shape Constructor\n";}
	};

	class Point: public Shape {
		public:
			Point() {cout << "In Point Constructor\n";}
	};
};

void pitfall_test_constructor_order() {
	test_constructor::Point p;
}

namespace test_pure_virtual_function {
	class Shape {
		public:
			Shape() {
				cout << "In Shape Constructor\n";
				print();
			}
		private:
			virtual void print() = 0;
	};

	class Point : public Shape {
		public:
			Point() {
				cout << "In Point Constructor\n";
			}
		private:
			void print() {
				cout << "In Point Print()\n";
			}
	};
};

void pitfall_pure_virtual_function () {
	test_pure_virtual_function::Point p;
	// will never success...
	// The previous line calls pure virtual function...
	cout << "Successfully initialize a Point instance p\n";
}

namespace test_virtual_and_pure_virtual {
	class Shape {
		public:
			virtual void foo_virtual() {
				cout << "virtual in Shape\n";
			}
			virtual void foo_virtual_2() {
				cout << "virtual 2 in Shape\n";
			}
			virtual void foo_pure_virtual() = 0;
	};
	class Point:public Shape {
		public:
			// I didn't implement the virtual function foo_virtual here. It works fine. When I call foo_virtual using a Point, the foo_virtual function of Shape will be called.
			void foo_virtual_2() {
				cout << "virtual 2 in Point\n";
			}
			void foo_pure_virtual() {
				cout << "pure virtual in Point\n";
			}
	};
};

void pitfall_virtual_and_pure_virtual () {
	test_virtual_and_pure_virtual::Point p;
	p.foo_virtual();
	p.foo_virtual_2();
	p.foo_pure_virtual();
	test_virtual_and_pure_virtual::Shape & s = p;
	// This should compile
	s.foo_virtual();
	s.foo_virtual_2();
}

int main(int argc, char* argv[]) {

	// pitfall_constructor_1();
	// pitfall_constructor_2();
	// pitfall_new_1();
	// pitfall_constructor_initialize_members();
	// pitfall_constructor_default_arguments();
	// pitfall_constructor_virtual_function();
	// pitfall_test_constructor_order();
	// pitfall_pure_virtual_function();
	pitfall_virtual_and_pure_virtual();
}
