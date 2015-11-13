#include<iostream>
#include<time.h>

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

int main() {

	// get_some_input();
	// using_tab_in_cout();
	guessing_random_number();
}
