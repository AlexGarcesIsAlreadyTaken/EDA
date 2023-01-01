#include <iostream>
#include <vector>
using namespace std;

//Returns all the diferent ways we can give 'x' change with at most 2 coins of each one in 's'
//0 <= i <= s.size()
int maneres(int x, int p, const vector<int>& s, vector<bool>& v, int i) {
	if (p > x or i > s.size()) return 0;
	if (p == x) return 1;
	int res = 0;
	int j = 2*i; int z = 2*i+1;
	v[j] = true; v[z] = false;
	if (s[i] + p <= x) res += maneres(x, p + s[i], s, v, i+1);
	v[j] = true; v[z] = true;
	if (2*s[i] + p <= x) res += maneres(x, p + 2*s[i], s, v, i+1);
	v[j] = false; v[z] = false;
	res += maneres(x, p, s, v, i+1);
	return res;
}

int main() {
	int x, n;
	while (cin >> x >> n) {
		vector<int> m(n);
		for (int i = 0; i < n; ++i) cin >> m[i];
		vector<bool> m2(2*n, false);
		cout << maneres(x, 0, m, m2, 0) << endl;
	}
}
