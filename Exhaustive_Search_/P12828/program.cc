#include <iostream>
#include <vector>
using namespace std;

void escriu(const vector<bool>& v) {
	int n = v.size();
	for (int i = 0; i < n; ++i) {
		if (i != 0) cout << ' ';
		cout << v[i];
	}
	cout << endl;
}

void binari(vector<bool>& v, int i) {
	int n = v.size();
	if (i == n) escriu(v);
	else {
		v[i] = false; binari(v, i+1);
		v[i] = true; binari(v, i+1);
	}
}

int main() {
	int n; cin >> n;
	vector<bool> v(n);
	binari(v, 0);
}
