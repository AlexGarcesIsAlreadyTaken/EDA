#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef vector<string> llista;

void escriu(const llista& v) {
	int n = v.size();
	cout << '(' << v[0];
	for (int i = 1; i < n; ++i) cout << ',' << v[i];
	cout << ')' << endl;
}

void permuta(map<int, bool>& afegit, const llista& L, llista& v, int i) {
	int n = v.size();
	if (i == n) escriu(v);
	else for (int j = 0; j < n; ++j) {
		if (not afegit[j]) {
			afegit[j] = true;
			v[i] = L[j]; permuta(afegit, L, v, i+1);
			afegit[j] = false;
		}
	}
}

int main() {
	int n;
	cin >> n;
	llista v(n);
	llista L(n);
	map<int, bool> afegit;
	for (int i = 0; i < n; ++i) {
		cin >> L[i];
		afegit.insert(make_pair(i, false));
	}
	permuta(afegit, L, v, 0);
}
