#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

void imprimeix(const vector<int>& v, int n) {
	cout << '{';
	for (int i = 0; i < n; ++i) {
		if (i != 0) cout << ',';
		cout << v[i];
	}
	cout << '}' << endl;
}

void troba_suma(int s, const vector<int>& v, vector<int>& res, int j, int aux) {
	if (s == 0 and aux == v.size()) {
		imprimeix(res, j);
		return;
	}
	if (aux == v.size()) return;
		res[j] = v[aux];
		troba_suma(s - v[aux], v, res, j+1, aux+1);
		troba_suma(s, v, res, j, aux+1);
}

int main() {
	int s; cin >> s;	// valor de suma
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}
	sort(v.begin(), v.end());
	vector<int> res(n);
	troba_suma(s, v, res, 0, 0);
}
