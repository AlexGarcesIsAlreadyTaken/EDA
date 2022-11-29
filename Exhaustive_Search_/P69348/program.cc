#include <iostream>
#include <vector>
using namespace std;

void escriu(const vector<int>& v) {
	int n = v.size();
	cout << '(' << v[0];
	for (int i = 1; i < n; ++i) cout << ',' << v[i];
	cout << ')' << endl;
}

void permuta(vector<bool>& afegit, vector<int>& v, int i) {
	int n = v.size();
	if (i == n) escriu(v);
	else for (int j = 1; j <= n; ++j) {
		if (not afegit[j-1]) {
			afegit[j-1] = true;
			v[i] = j; permuta(afegit, v, i+1);
			afegit[j-1] = false;
		}
	}
}

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	vector<bool> afegit(n);
	permuta(afegit, v, 0);
}
