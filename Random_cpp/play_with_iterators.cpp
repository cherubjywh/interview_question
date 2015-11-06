#include<vector>
#include<iostream>

using namespace std;

// I haven't got chance to check this part yet. I will get it fixed on Sat

void update_vector(vector<int>::iterator it) {
	*it = 0;
}

int main(int argc, char *argv[]) {
	vector<int> v;
	update_vector(v.begin());
	cout << v[0];
}
