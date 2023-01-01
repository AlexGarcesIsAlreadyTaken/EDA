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

void se(vector<char>& v, set<char>& especies, const vector<vector<bool> >& VS, int i) {
	if (i >= v.size()) return;
	for (auto it = especies.begin(); it != especies.end(); ++it) {
		char c = *it;
		if (i != 0) {
			char C = v[i-1];
			int j, z;
			if ('A' <= C and C <= 'Z') j = C - 'A';
			else j = C - 'a' + ALPHABET;
			if ('A' <= c and c <= 'Z') z = c - 'A';
			else z = c - 'a' + ALPHABET;	// Observem la ultima lletra afegida
			if (VS[j][z]) continue;				//Si no es conflictiva la actual i la anterior
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
	vector<vector <bool> > VS(52, vector<bool>(52));
	for (int i = 0; i < m; ++i) {
		char a, b; cin >> a >> b;
		especies.insert(a);
		int j, z;
		if ('A' <= a and a  <= 'Z') j = a - 'A';
		else j = a - 'a' + ALPHABET;
		
		if ('A' <= b and b  <= 'Z') z = b - 'A';
		else z = b - 'a' + ALPHABET;

		VS[j][z] = true;
		VS[z][j] = true;
	}
	vector<char> v(n);
	se(v, especies, VS, 0);
}
