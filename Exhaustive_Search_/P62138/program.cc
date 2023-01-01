#include <iostream>
#include <list>
#include <vector>
using namespace std;

typedef int vertex;
typedef vector<vertex> llista_pares;
typedef vector<llista_pares> graf;

void imprimeix(const list<vertex>& Q) {
	for (auto it = Q.begin(); it != Q.end(); ++it) {
		if (it != Q.begin()) cout << ' ';
		cout << *it;
	}
	cout << endl;
}

void ordenacions(const graf& G, list<vertex>& Q, vector<bool>& visitat) {
	if (Q.size() == 0) { //Primera insercio. Que no tingui tasques prioritaries
		for (int i = 0; i < G.size(); ++i) {
			if (G[i].size() == 0) {
				visitat[i] = true; Q.push_back(i);
				if (Q.size() == G.size()) imprimeix(Q);
				else ordenacions(G, Q, visitat);
				visitat[i] = false; Q.pop_back();
	}	}	}
	//Insercio general. Que no tingui o hagin conclos totes les tasques prioritaries
	else for (int i = 0; i < G.size(); ++i) {
		if (visitat[i]) continue;	//Aquesta tasca ja s'ha realitzat
															
		bool apte = true;
		for (vertex w : G[i]) if (not visitat[w]) {
			apte = false;
			break;
		}
		if (not apte) continue;	//Passa a la seguent tasca, aquesta encara te de prioritzades
		visitat[i] = true; Q.push_back(i);
		if (Q.size() == G.size()) imprimeix(Q);
		else ordenacions(G, Q, visitat);
		visitat[i] = false; Q.pop_back();
}	}

int main() {
	int n, m; cin >> n >> m;
	graf G(n, llista_pares(0));
	for (int i = 0; i < m; ++i) {
		vertex x, y; cin >> x >> y;
		G[y].push_back(x);
	}
	vector<bool> visitat(n, false);
	list<vertex> Q;
	ordenacions(G, Q, visitat);
}
