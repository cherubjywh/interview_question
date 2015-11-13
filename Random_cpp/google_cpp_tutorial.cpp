#include<iostream>

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

int main() {

	// get_some_input();
	using_tab_in_cout();
}
