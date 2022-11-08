#include <iostream>
#include <vector>
using namespace std;

typedef pair<int,int> vertex;
typedef vector<char> fila;
typedef vector<fila> matriu;

void dfs_pinta(matriu& mapa, int x, int y) {

	vertex aux;
	if (mapa[x][y+1] == '.') {
		mapa[x][y+1] = mapa[x][y];
		dfs_pinta(mapa, x, y+1);
	}
	if (mapa[x][y-1] == '.') {
		mapa[x][y-1] = mapa[x][y];
		dfs_pinta(mapa, x, y-1);
	}
	if (mapa[x+1][y] == '.') {
		mapa[x+1][y] = mapa[x][y];
		dfs_pinta(mapa, x+1, y);
	}
	if (mapa[x-1][y] == '.') {
		mapa[x-1][y] = mapa[x][y];
		dfs_pinta(mapa, x-1, y);
	}
}

void pinta(matriu& mapa, const vector<vertex>& V) {
	for(vertex v: V) {
		dfs_pinta(mapa, v.first, v.second);
	}
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		
		matriu mapa(n, fila(m));
		vector<vertex> punt_partida;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> mapa[i][j];
				if (mapa[i][j] != '#' and mapa[i][j] != '.') 
					punt_partida.push_back(make_pair(i, j));
			}
		}

		pinta(mapa, punt_partida);

		for (int i = 0; i < n; ++i) { 
			for (int j = 0; j < m; ++j) 
				cout << mapa[i][j];
			cout << endl;
		}
		cout << endl;
	}
}
