#include <unordered_set>
#include <set>
#include <vector>
#include <iostream>
using namespace std;

#define ALPHABET 'Z' - 'A' + 1

void escriu(vector<char>& v) {
	for (int i = 0; i < v.size(); ++i) cout << v[i];
	cout << endl;
}

void se(vector<char>& v, set<char>& especies, const vector<unordered_set<char> >& VS, int i) {
	if (i >= v.size()) return;
	for (auto it = especies.begin(); it != especies.end(); ++it) {
		char c = *it;
		if (i != 0) {
			char z = v[i-1];
			int j = -1;
			if ('A' <= z and z <= 'Z') j = z - 'A';
			else j = z - 'a' + ALPHABET; // Observem la ultima lletra afegida
			if (VS[j].find(c) != VS[j].end()) continue;	//Si no es conflictiva la actual i la anterior
																									//la afegim a v
																									//si no probem una altra lletra
		}
		especies.erase(it);
		v[i] = c;
		if (i+1 == v.size()) escriu(v);
		else se(v, especies, VS, i+1);
		it = especies.insert(c).first;
	}
}

int main() {
	int n;	// 1 <= n <= 52
	cin >> n;
	set<char> especies;
	for (int i = 0; i < n; ++i) {
		char c; cin >> c;
		especies.insert(c);
	}
	int m; cin >> m;
	vector<unordered_set<char> > VS(52);
	for (int i = 0; i < m; ++i) {
		char a, b; cin >> a >> b;
		especies.insert(a);
		if ('A' <= a and a  <= 'Z') VS[a - 'A'].insert(b);
		else VS[a - 'a' + ALPHABET].insert(b);

		if ('A' <= b and b  <= 'Z') VS[b - 'A'].insert(a);
		else VS[b - 'a' + ALPHABET].insert(a);
	}
	vector<char> v(n);
	se(v, especies, VS, 0);
}
