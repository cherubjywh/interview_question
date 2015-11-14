#include<iostream>
#include<time.h>
#include<cmath>

using namespace std;

void get_some_input() {
	int input_var = 0;
	do {
		cout << "Enter a number (-1 = quit):";
		if (!(cin >> input_var)) {
			cout << "Input Error. Cleaning..." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
			// recover from the error
			// cin.clean();
			// cin.ignore();
		}

		if (input_var == -1) {
			break;
		}

		cout << "You entered " << input_var << endl;
	} while (1);
	cout << "All done." << endl;
}

void using_tab_in_cout () {
	cout << " 1\t2\t3\t4\t5\t6\t7\t8\t9" << endl << "" << endl;
	for (int c = 1; c < 10; c++) {
		cout << c << "|";
		for (int i = 1; i < 10; i++) {
			cout << i * c << '\t';
		}
		cout << endl;
	}
}

void guessing_random_number() {

	int input_val;
	int target_val;

	while(1) {
		srand(time(NULL));
		target_val = rand() % 10 + 1;
		cout << "Target number: " << target_val << endl;
		while (1) {
			cout << "Enter a number: ";
			if (!(cin >> input_val)) {
				cin.clear();
				cin.ignore(10000, '\n');
			}
			if (input_val == -1) {
				cout << "Exit game!" << endl;
				return;
			}
			if (input_val == target_val) {
				cout << "You win!" << endl;
				break;
			}
		}
	}
}

int greatest_common_divisor(int a, int b) {
	// Euclidean algorithm
	if (a < b) swap(a, b);
	int r = a % b;
	while (r != 0) {
		a = a % b;
		swap(a, b);
		r = a % b;
	}
	return b;
}

void math_puzzles () {
	double a = 10, b = 3, c = 0.5;
	double target = 100;

	int max_guess = static_cast<int>(400/14);

	for (int i = 1; i <= max_guess; ++i) {
		int j = static_cast<int>((400 + i * 14)/5);

		if (j >= 1 && fabs(i * 14 - 5 * j + 400) < 1e-6 && (i + j) <= 100) {
			cout << "a: " << i << ", b: " << 100 - i - j << ", c: " << j << endl;
		//	return;
		}
			
	}
}



int main() {

	// get_some_input();
	// using_tab_in_cout();
	// guessing_random_number();
	// cout << greatest_common_divisor(-4, 14) << endl;
	math_puzzles();

	return 0;
}
