#include<iostream>
#include<string>
#include<cmath>
#include<iostream>
#include<fstream>
#include<list>
#include<vector>

/*
   This file is intened for testing many pitfalls of using C++. There are multiple (tricky) traps in the code... And several warnings even the code compiles...

   The code is to help me be prepared and aware of all the pitfalls in wrting C++ code...

   */

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

namespace virtual_destructor{
	class Employee {
		public:
			Employee(string name) : _name(name) {
				cout << "In Constructor of Employee\n";
			}
			// I got these words from Stack Overflow: To sum up, always make base classes' destructors virtual when they're meant to be manipulated polymorphically.
			virtual ~Employee() {
				cout << "In Destructor of Employee\n";
			}
			/*

			   // This is a wrong demonstration of destructor function: It will cause memory leaking if it is used polymorphically.
			   // The destructor of inherited class will not be call due to static binding

			~Employee() {
				cout << "In Destructor of Employee\n";
			}
			*/

		private:
			string _name;
	};

	class Manager: public Employee {
		public:
			// Because there is no default constructor, the inherite class must explicitly initialize parent class.
			Manager(string name, string dept):Employee(name), _dept(dept) {
				cout << "In Constructor of Manager\n";
			}
			~Manager() {
				cout << "In Destructor of Manager\n";
			}
		private:
			string _name;
			string _dept;
	};
};

void pitfall_virtual_destructor() {
	using namespace virtual_destructor;
	//Manager m("AA", "BB");
	Employee* e = new Manager("AA", "BB");	
	delete e;
}

namespace double_free_destructor {
	class Employee {
		public:
			Employee(string name) : _name(name) {}
			virtual ~Employee() {}
			string get_name() const {return _name;}
		protected:
			string _name;
	};

	class Manager: public Employee {
		// Moral: A class with a destructor needs a copy constructor
		// The Big 3: It is not just a good idea -- it is the law (Marshall Cline)
		// The original example is not quite good for explaining why both copy constructor and overloading operator are necessary
		// They are for different ocassions for sure, and cannot replace each other
		// Copy constructor is used for initializing an object
		// = is used for overwriting or assiging one object to another existing object
		// One more note: use const to add more conditions, and force the compilar to do more checks for you, maily for the purpose of getting semantic correct
		public:
			Manager(string name, string sname) : Employee(name), _secretary(new Employee(sname)) {}
			Manager(Manager& m): Employee(m.get_name()), _secretary(new Employee(m.get_sname())) {
				cout << "In Manger's copy Constructor\n";
			}
			Manager& operator=(const Manager& m) {
				cout << "In Manger's overloading operator function\n";


				_name = m.get_name();
				if (_secretary != nullptr) {
					delete _secretary;
				}
				_secretary = new Employee(m.get_sname());
				return *this;
			}
			string get_sname() const {return _secretary -> get_name();}
			~Manager() {delete _secretary;}
		private:
			Employee* _secretary;
	};
};

void pitfall_double_free_destructor () {
	using namespace double_free_destructor;
	Manager m1("AA", "BB");
	Manager m2 = m1;
	Manager m3("CC", "DD");
	m3 = m2;
}

namespace inheritance_pitfall_overriding {
	class Employee {
		public:
			virtual void print() {
				cout << "print() of Employee\n";
			}
	};

	class Manager : public Employee {
		public:
			virtual void print() {
				// need to explicitely specify that the print is from the base class
				Employee::print ();
				cout << "print() of Manager\n";
			}
	};
}

void pitfall_inheritance_overriding () {
	using namespace inheritance_pitfall_overriding;
	Manager m;
	m.print();
}

namespace inheritance_pitfall_pointer {
	class Employee {
		public:
			Employee(string name):_name(name){}
			string get_name() const {return _name;}
			void print() {
				cout << "print of Employee\n";
				cout << _name << endl;
			}
		protected:
			string _name;
	};
	class Manager: public Employee {
		public:
			Manager(): Employee("foo"){
				_sname = "bar";
			}
			Manager(string name, string sname):Employee(name), _sname(sname){}
			string get_sname() const {return _sname;}
			Manager& operator=(const Manager& m) {
				_name = m.get_name();
				_sname = m.get_sname();
				return *this;
			}
			//void print() {cout << "print of Manager\n";}
		private:
			string _sname;
	};
	void pitfall_function(Employee* e, int sz) {
		// *** the sizeof(Employee) is not the same as sizeof(Manager)
		// So the e[1] is not working as expected
		// We want to print A2, but it is actually prints B1
		if (sz > 1) {
			e[1].print();
		}
	}
};

void pitfall_inheritance_pointer () {
	using namespace inheritance_pitfall_pointer;
	Manager m[2];
	m[0] = Manager("A1", "B1");
	m[1] = Manager("A2", "B2");
	pitfall_function(m, 2);
	cout << "sizeof(Employee): " << sizeof(Employee) << endl;
	cout << "sizeof(Manager): " << sizeof(Manager) << endl;
}

namespace pitfall_operator_assignment{
	class Employee {
		public:
			Employee(char *name); 
			Employee(const Employee&);
			Employee& operator=(const Employee&);
			virtual ~Employee() {delete _name;}
		protected:
			char * _name;
	};

	class Manager: public Employee {
		public:
			Manager(char *name, char *dept);
			Manager(const Manager& m) ;
			Manager &operator=(const Manager&);	
			virtual ~Manager() {delete _dept;}
			void print() {
				printf("dept: %s\n", _dept);
				printf("name: %s\n", _name);
			}
		private:
			char * _dept;
	};


	Employee::Employee(char *name): _name(new char[strlen(name) + 1]) {
		strcpy(_name, name);
	}

	Employee::Employee(const Employee& e) : _name(new char[strlen(e._name) + 1]){
		strcpy(_name, e._name);	
	}

	Employee& Employee::operator=(const Employee& e) {
		delete _name;
		_name = new char[strlen(e._name) + 1];
		strcpy(_name, e._name);
		return *this;
	}

	/*
		If you don't speciy a call of base class Constructor, the default Constructor will be called, if any

	   */

	Manager::Manager(char *name, char* dept) : Employee(name), _dept(new char[strlen(dept) + 1]) {
		strcpy(_dept, dept);
	}


	Manager::Manager(const Manager& m) : Manager(m._name, m._dept){
		_dept = new char[strlen(m._dept) + 1] ;
		strcpy(_dept, m._dept);	
	}

	Manager& Manager::operator=(const Manager& m) {
		// Here need to explicitely call base class copy operator
		Employee::operator=(m);
		delete _dept;
		_dept = new char[strlen(m._dept) + 1];
		strcpy(_dept, m._dept);
		return *this;
	}
};

void pitfall_inheritance_assign_op () {
	using namespace pitfall_operator_assignment;
	string AA = "AA";
	string BB = "BB";
	char * AA_char = new char[AA.size() + 1];
	char * BB_char = new char[BB.size() + 1];
	copy(AA.begin(), AA.end(), AA_char);
	copy(BB.begin(), BB.end(), BB_char);
	Manager m1(AA_char, BB_char);
	Manager m2(BB_char, AA_char);
	cout << "Before ----\n";
	m2.print();
	m2 = m1;
	cout << "After ----\n";
	m2.print();

	delete AA_char;
	delete BB_char;
}


namespace pitfall_default_constructor {
	class A {
		public:
			A() {}
			A(int a) {}
	};

	class B:public A {
		public:
			B() {}
	};
};

void pitfall_test_default_constructor () {
	using namespace pitfall_default_constructor;
	B b;
}

void pitfall_stream () {
	list <int> a;

	// Moral: eof() is only useful in combination with fail(), to find out whether EOF was the cause for failure
	ofstream myfile;
	myfile.open("data.txt");
	if (myfile.is_open()) {
		myfile << "1\n2\n3\n4\n11\n12\n13\n14\n";
	}
	myfile.close();


	myfile.open("data.txt", ios::out | ios::app);
	if (myfile.is_open()) {
		myfile << "21\n22\n23\n24";
	}
	myfile.close();

	ifstream myinfile;
	myinfile.open("data.txt");
	if (myinfile.is_open()) {
		string line;
		// Moral: do not use eof() to check if the whole file has been read through; eof() is only used to check failure status
		// Because if the stream state turns to fail, the end of file will never be reached. Such that the checking condition will never be reached. If we use that condition in the while loop, the loop will never stop.
		// other useful functions: bad, eof, good, fail
		while (getline(myinfile, line)) {
			a.push_back(stoi(line));
		}
	}

	myinfile.close();

	for (auto i : a) {
		cout << i << " ";
	}
	cout << endl;


	list<int> b;

	myinfile.open("data.txt");

	// My note:
	// eof() ==> not good()
	// eof() <> fail()
	
	if (myinfile.is_open()) {
		int x;
		while (myinfile.good()) {
			myinfile >> x;
			if (myinfile.good()) b.push_back(x);
		}
	}
	myinfile.close();

	for (auto i : b) {
		cout << i << " ";
	}
	cout << endl;


	// The remdy is here, use fail() function
	// Only fail is useful among all 4 status flags
	list<int> c;

	myinfile.open("data.txt");

	if (myinfile.is_open()) {
		int x;
		while (myinfile) {
			myinfile >> x;
			if (myinfile) c.push_back(x);
		}
	}

	myinfile.close();

	for (auto i : c) {
		cout << i << " ";
	}
	cout << endl;

}

namespace pitfall_operator_overloading {
	class Complex {
		public:
			Complex (double re = 0.0, double im = 0.0):_re(re), _im(im) {
				cout << "In Standard Constructor of Complex\n";
			}
			Complex (const Complex &b):_re(b._re), _im(b._im) {
				cout << "In Copy Constructor of Complex\n";

			}
			Complex operator+ (const Complex& b) const {
				return Complex(_re + b._re, _im + b._im);
			}
			Complex operator* (const Complex& b) const {
				return Complex(_re*b._re - _im*b._im, _re*b._im + _im*b._re);
			}
			Complex operator/ (const Complex& b) const {
				// (a + bi)/(c + di)
				// = (ac - bd + (ad + bc)i)/(cc -dd + 2(cd)i)
				double num_re = _re * b._re - _im * b._im;
				double num_im = _re * b._im + _im * b._re;
				double denum = b._re * b._re - b._im * b._im + 2.0 * b._re * b._im;
				return Complex(num_re/denum, num_im/denum);
			}
			Complex operator^(const Complex& b) const {
				// I don't really know how to compute this...
				cout << "In Operator ^ of Complex\n";
				return Complex(pow(_re, b._re), 0);
			}
			Complex & operator=(const Complex& b) {
				_re = b._re;
				_im = b._im;

				return *this;
			}

			// Two ways to overload <<
			// 1. Make << a frind function of the class

			friend ostream& operator<<(ostream& os, Complex & b) {
				os << b._re << " + " << b._im << "i";
				return os;
			}


			// 2. Make << a member of the class
			ostream& operator<<(ostream& os) {
				os << _re << "+" << _im << "i";
				return os;
			}

		private:
			double _re;
			double _im;
	};
};

void pitfall_operator_precedence () {
	using namespace pitfall_operator_overloading;
	Complex i(2, 1);
	Complex j((i ^ (2.0 + 1)));
	Complex k(j);
	// quite tricky
	// k + 1.0 return something, which will be able to access out of the original function
	cout << (k = k + 1.0) << endl;
	cout << k << endl;
}


namespace pitfall_array_grow_size {
	class Array {
		public:
			Array(): _n(0), _a(nullptr){}
			~Array() {
				delete[] _a;
				cout << "In Destructor function of Array\n";
			}
			Array(const Array& b) {
				_n = b._n;
				_a = new int[_n];
				for (size_t i = 0; i < _n; ++i) {
					_a[i] = b._a[i];
				}
			}
			Array &operator=(const Array& b) {
				if (_a) {
					delete[] _a;
				}
				_n = b._n;
				_a = new int[_n];
				for (size_t i = 0; i < _n; ++i) {
					_a[i] = b._a[i];
				}

				return *this;
			}
			int &operator[](size_t i) {
				// It is a pretty bad idea to change the size of array by moving the whole new array
				if(i >= _n) {
					int *p = new int[i + 1];
					for (size_t index = 0; index < _n; ++index) {
						p[index] = _a[index];
					}
					for (size_t index = _n; index <= i; ++index) {
						p[index] = 0;
					}
					delete[] _a;
					_n = i + 1;
					_a = p;

				}
				return _a[i];
			}
			friend ostream& operator<< (ostream& os, const Array& a) {
				if (a._n == 0) 
					return os;

				for (size_t i = 0; i < a._n - 1; ++i) {
					os << a._a[i] << ", ";
				}
				os << a._a[a._n - 1];
				return os;
			}
		private:
			size_t _n;
			int* _a;
	};
};

void pitfall_array_operator() {
	//using namespace pitfall_array_grow_size;
	pitfall_array_grow_size::Array a;
	a[0] = 1;
	a[1] = 2;
	cout << &(a[0]) << endl;
	a[2] = 3;
	cout << &(a[0]) << endl;
	cout << a << endl;
}


// Note: auto_ptr, only one auto_ptr can own a heap object

void pitfall_auto_ptr () {
	// auto_ptr: smarter pointer, will release resources once the referred objects are not useful any more
	auto_ptr<vector<int>> pt(new vector<int>());
	pt -> push_back(0);
	pt -> push_back(1);
	pt -> push_back(2);
	// The we do the copy. And the ownership of the vector will be handed over from pt to pt1
	auto_ptr<vector<int>> pt1 = pt;
	// The following line will not cause problem when we try tor compile it, but will cause problem in the running time. Since it is a null pointer already
	// cout << pt -> size() << endl;
	cout << pt1 -> size() << endl;
	// It is very elegant to pass and return pointers using auto_ptr. Be sure to only use auto_ptr like that!!!
	// Auto_ptr is not a "normal" object, the semantic meaning of copy is not the same as other objects
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
	// pitfall_virtual_and_pure_virtual();
	// pitfall_virtual_destructor();
	// pitfall_double_free_destructor();
	// pitfall_inheritance_overriding();
	// pitfall_inheritance_pointer();
	// pitfall_inheritance_assign_op();
	// pitfall_test_default_constructor();
	// pitfall_stream();
	// pitfall_operator_precedence();
	// pitfall_array_operator();
	pitfall_auto_ptr();

}
