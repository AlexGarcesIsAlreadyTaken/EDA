#include <iostream>
#include <list>
#include <vector>
#include <set>
using namespace std;

typedef unsigned int vertex;
typedef vector<vertex> llista_fills;
typedef vector<llista_fills> graf;

void imprimeix(const vector<vertex>& L) {
	for (int i = 0; i < L.size(); ++i) {
		if (i != 0) cout << ' ';
		cout << L[i];
	}
	cout << endl;
}

void ordenacions(const graf& G, vector<vertex>& L, vector<bool>& visitat, vector<int>& pares, set<vertex>& S, int i) {
	if (i >= G.size()) return;
	//Que no tingui o hagin conclos totes les tasques prioritaries
	for (auto it = S.begin(); it != S.end(); ++it) {
		vertex w = *it;
		if (visitat[w]) continue;

		for (vertex v : G[w])	if (--pares[v] == 0) S.insert(v);
		
		visitat[w] = true; L[i] = w; S.erase(it);	
		if (i+1 == G.size()) imprimeix(L);
		else ordenacions(G, L, visitat, pares, S, i+1);
		visitat[w] = false; it = S.insert(w).first;

		for (vertex v : G[w]) if (++pares[v] == 1) S.erase(v);
}	}

int main() {
	int n, m; cin >> n >> m;
	graf G(n, llista_fills(0));
	vector<int> pares(n, 0);
	for (int i = 0; i < m; ++i) {
		vertex x, y; cin >> x >> y;
		G[x].push_back(y);
		++pares[y];
	}
	vector<bool> visitat(n, false);
	vector<vertex> L(n);
	set<vertex> S; for (int i = 0; i < pares.size(); ++i) if (pares[i] == 0) S.insert(i); 
	ordenacions(G, L, visitat, pares, S, 0);
}
