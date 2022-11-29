#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef map<char, bool> sac;

void escriu(const vector<char>& v) {
	for (int i = 0; i < v.size(); ++i) cout << v[i];
	cout << endl;
}

//	Agafarem la lletra del sac usa. En la seguent crida usarem el sac aux, aixi recursivament
void forma_par(vector<char>& par, sac& usa, sac& aux, int k) {
	int n = par.size();
	if (k == n) escriu(par);
	else {
		for (auto it = usa.begin(); it != usa.end(); ++it) 
			if (not it->second) {
				it->second = true;
				par[k] = it->first; forma_par(par, aux, usa, k+1);
				it->second = false;
			}
	}
}

int main() {
	int n; cin >> n;
	sac cons;	
	vector<char> par(2*n);
	for (int i = 0; i < n; ++i) {
		char c; cin >> c;
		cons.insert(make_pair(c, false));
	}
	sac voc;
	for (int i = 0; i < n; ++i) {
		char v; cin >> v;
		voc.insert(make_pair(v, false));
	}
	forma_par(par, cons, voc, 0);
}
