#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

void print(vector<int>::iterator beg, vector<int>::iterator en) {
	while (beg != en) {
		cout << *beg << " ";
		beg++;
	}

	cout << endl;
}

void quick_sort(vector<int>::iterator beg, vector<int>::iterator en) {

	if (beg == en) {
		return;
	}

	auto i = beg + 1;
	auto j = i;

	while (j != en) {
		if (*beg > *j) {
			swap(*i, *j);
			++i;
		}
		++j;
	}

	swap(*(i - 1), *beg);
	quick_sort(beg, i - 1);
	quick_sort(i, en);
}

int select(vector<int>::iterator beg, vector<int>::iterator en, int target) {
	if (target == 0) {
		return *beg;
	}
    
	auto i = beg + 1;
	auto j = i;


	while (j != en) {
		if (*beg > *j) {
			swap(*i, *j);
			++i;
		}
		++j;
	}
	swap(*(i - 1), *beg);

	int len_first = (int)(i - 1 - beg);
	cout << (en - beg) << " " << len_first << " " << target << endl;
	if (len_first == target) {
		return *(i - 1);
	} else if (len_first < target) {
		return select(i, en, target - len_first - 1);
	} else {
		return select(beg, i - 1, target);
	}

}

int main(int argc, char* argv[]) {
	//vector<int> A = {2, 0, 7, 3, 5, 4, 1, 2, 2};
	/*
	vector<int> A = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
	*/

	vector<int> A;
	ifstream f("/Users/sunyuyin/Documents/Workspace/CPP/interview_questions/Random_cpp/select_test_case.txt");
	if (!f.is_open()) {
		cerr << "bad file\n";
		exit(-1);	
	}
	
	string s;
	if (!getline(f, s)) {
		f.close();
		exit(-1);
	}
	istringstream ss(s);

	string val;
	while (ss) {
		getline(ss, val, ',');
		A.push_back(stoi(val));
	}
	cout << endl;

	f.close();
	
	cout << select(A.begin(), A.end(), 10000) << endl;
/*
	quick_sort(A.begin(), A.end());
	print(A.begin(), A.end());
	*/

}
