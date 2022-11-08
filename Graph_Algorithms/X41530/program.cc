#include <iostream>
#include <vector>
using namespace std;

typedef int vertex;
typedef vector<vertex> llista_adj;
typedef vector<llista_adj> graf;


/* Retorna false si hi ha un cicle a G, true altrament */
bool dfs(const graf& G, vertex pare, vertex v, vector<bool>& visitat) {
	visitat[v] = true;
	for (auto w : G[v]) {
		bool aux = visitat[w];
		if (not aux and not dfs(G, v, w, visitat)) return false;
		if(aux and w != pare) return false;
	}
	return true;
}

bool es_bosc(const graf& G, int& arbres) {
	int n = G.size();
	vector<bool> visitat(n, false);
	for (int v = 0; v < n; ++v) {
		if (not visitat[v]) {
			++arbres;
			if (not dfs(G, v, v, visitat)) return false; 
		}
	}
	return true;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		graf G(n, llista_adj(0));
		for (int i = 0; i < m; ++i) {
			int x, y;
			cin >> x >> y;
			G[x].push_back(y);
			G[y].push_back(x);
		}
		int arbres = 0;
		if (es_bosc(G, arbres)) cout << arbres << endl;
		else cout << "no" << endl;
	}
}
