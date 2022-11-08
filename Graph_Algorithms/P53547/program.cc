#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

typedef pair<int, int> vertex;

typedef vector<int> fila;
typedef vector<fila> matriu;

int num_alfils(matriu& G, int x, int y, int& caselles) {
	caselles++;
	int total = G[x][y];
	G[x][y] = -1;
	if (G[x+1][y+1] != -1) total += num_alfils(G, x+1, y+1, caselles);
	if (G[x+1][y-1] != -1) total += num_alfils(G, x+1, y-1, caselles);
	if (G[x-1][y+1] != -1) total += num_alfils(G, x-1, y+1, caselles);
	if (G[x-1][y-1] != -1) total += num_alfils(G, x-1, y-1, caselles);
	return total;
}

bool mateix_numero(matriu& G, const vector<vertex>& V) {
	int aux = -1;
	for (int v = 0; v < V.size(); ++v) {
		int x = V[v].first;
		int y = V[v].second;
		if (G[x][y] != -1) {
			int caselles = 0;
			int alfils = num_alfils(G, x, y, caselles);
			
			if (aux == -1) aux = alfils/caselles;
			if (alfils%caselles != 0 or alfils != aux*caselles) return false;
		}
	}
	return true;
}

int main() {
	int t; cin >> t;
	for (int k = 1; k <= t; ++k) {
		int n, m;
		cin >> n >> m;
		matriu tauler(n + 2, fila(m + 2));
		
		vector<vertex> alfils;

		for (int i = 0; i < n+2; ++i) {
			for (int j = 0; j < m+2; ++j) {
				if (i == 0 or j == 0 or i == n+1 or j == m+1) tauler[i][j] = -1;
				else {
					string aux; cin >> aux;
					if (aux == "X") tauler[i][j] = -1;
					else {
						int v = atoi(aux.c_str());	
						tauler[i][j] = v;
						alfils.push_back(make_pair(i, j));
					}
				}
			}
		}
		bool p = mateix_numero(tauler, alfils);
		cout << "Case " << k << ": ";
		if (p) cout << "yes" << endl;
		else cout << "no" << endl;


		/*
		for (int i = 0; i < n+2; ++i) {
			for (int j = 0; j < m+2; ++j) {
				if (tauler[i][j] == -1) cout << "X ";
				else cout << tauler[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;*/
	}
}
