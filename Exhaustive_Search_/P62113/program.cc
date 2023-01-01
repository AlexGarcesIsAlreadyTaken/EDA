#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void escriu(int x, const vector<int>& s, const vector<bool>& v, const vector<bool>& vp) {
	cout << x << " = ";
	bool first = true;
	for (int i = 0; i < s.size(); ++i) {
		int j = s[i];
		if (v[j]) {
			if (not first) cout << " + ";
			cout << j;
			first = false;
		}
		if (vp[j]) {
			if (not first) cout << " + ";
			cout << j << 'p';
			first = false;
		}
		
	}
	cout << endl;
}

void permuta(int x, int p, const vector<int>& s, vector<bool>& v, vector<bool>& vp, int i) {
	if (i > s.size() or p > x) return;
	if (p == x) {escriu(x, s, v, vp); return;}
	while (i < s.size()) {
		int j = s[i];
		if (not v[j]) {
			v[j] = true; permuta(x, p+j, s, v, vp, i); v[j] = false;
		}
		vp[j] = true; permuta(x, p+j, s, v, vp, i+1); vp[j] = false;
		++i;
	}
}

int main() {
	int x, n;
	while (cin >> x >> n) {
		vector<bool> v(1001, false);
		vector<bool> vp(1001, false);
		vector<int> s(n);
		for (int i = 0; i < n; ++i) cin >> s[i];
		sort(s.begin(), s.end());
		permuta(x, 0, s, v, vp, 0);
		cout << "----------" << endl;
	}
}
