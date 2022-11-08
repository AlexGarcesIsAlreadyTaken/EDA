#include <iostream>
#include <vector>
using namespace std;

int peak(const vector<int>& v, int l, int r) {
	int n = v.size();
	if (n == 1 or v[0] > v[1]) return 0;
	if (v[n-1] > v[n-2]) return n-1;
	int m = (l+r)/2;
	if (v[m] < v[m+1]) return peak(v, m+1, r);
	if (v[m] < v[m-1]) return peak(v, l, m-1);
	return m;
}

bool find(int x, const vector<int>& v, int l, int r, int p) {
	if (l > r) return false;
	int m = (l+r)/2;
//	cout << m << ' ' << v[m] << endl;
	if ((v[m] < x and p > m) or (v[m] > x and m > p)) return find(x, v, m+1, r, p);
	if ((v[m] > x and p > m) or (v[m] < x and m > p)) return find(x, v, l, m-1, p);
	return true;
}

bool search(int x, const vector<int>& v) {
	int n = v.size();
	int m = peak(v, 0, n-1);
//	cout << v[m] << endl;
	if (v[m] == x or v[0] == x or v[n-1] == x) return true;
	return find(x, v, 0, m-1, m) or find(x, v, m+1, n-1, m);
}

int main() {
	int n;
	while (cin >> n) {
		vector<int> v(n);
		for (int i = 0; i < n; ++i) cin >> v[i];
		int x; cin >> x;
		cout << (search(x, v) ? "true" : "false") << endl;
	}
}
