#include <iostream>
#include <vector>
using namespace std;

void escriu(const vector<bool>& v) {
	int n = v.size();
	cout << v[0];
	for (int i = 1; i < n; ++i) cout << ' ' << v[i];
	cout << endl;
}

void binari(vector<bool>& v,const int u, int k, int i) {
	int n = v.size();
	//n-i(nombres que queden per ompli) >= u-k(1s que he de ficar)
	if (k > u or n-i < u-k) return;
	if (i == n) {
		escriu(v);
	}
	else {
		v[i] = false; binari(v, u, k, i+1);
		v[i] = true; binari(v, u, k+1, i+1);
	}
}
int main() {
	int n, u;
	cin >> n >> u;
	vector<bool> v(n);
	binari(v, u, 0, 0);
}
