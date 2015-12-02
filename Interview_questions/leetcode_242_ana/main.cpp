#include<string>
#include<algorithm>
#include<iostream>

using namespace std;


int main(int argc, char* argv[]) {
	string s = "dagafa";
	string t = "agdafa";

	cout << s << endl;
	sort(s.begin(), s.end());
	cout << s << endl;

	cout << t << endl;
	sort(t.begin(), t.end());
	cout << t << endl;

	cout << (s.compare(t) == 0) << endl;



}
