#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> vertex;
typedef vector<char> fila;
typedef vector<fila> graf;

int dist_min(graf& G, int x, int y) {
	if (G[x][y] == 'X') return -1;
	vector<vector<int>> D(G.size(), vector<int> (G[0].size()));
	D[x][y] = 0;
	queue<vertex> Q;
	Q.push(make_pair(x, y)); //Punt de partida
	while (not Q.empty()) {
		vertex v = Q.front(); Q.pop();
		int i = v.first;
		int j = v.second;
		int dist = D[i][j];
		if (G[i][j] == 't') return dist;
		G[i][j] = 'X';
		if (G[i+1][j] != 'X') {
			D[i+1][j] = dist+1;
			Q.push(make_pair(i+1, j));
		}
		if (G[i-1][j] != 'X') {
			D[i-1][j] = dist+1;
			Q.push(make_pair(i-1, j));
		}
		if (G[i][j+1] != 'X') {
			D[i][j+1] = dist+1;
			Q.push(make_pair(i, j+1));
		}
		if (G[i][j-1] != 'X') {
			D[i][j-1] = dist+1;
			Q.push(make_pair(i, j-1));
		}
	}
	return -1;
}

int main() {
	int n, m; cin >> n >> m;
	graf mapa(n+2, fila(m+2));
	for (int i = 0; i < n+2; ++i) {
		for (int j = 0; j < m+2; ++j) {
			if (i == 0 or i == n+1 or j == 0 or j == m+1) mapa[i][j] = 'X';
			else cin >> mapa[i][j];
		}
	}
	/*for (int i = 0; i < n+2; ++i) {
		for (int j = 0; j < m+2; ++j) {
			cout << mapa[i][j];
		}
		cout << endl;
	}*/
	int x, y; cin >> x >> y;
	int res = dist_min(mapa, x, y);
	if (res != -1) cout << "distancia minima: " << res << endl;
	else cout << "no es pot arribar a cap tresor" << endl;
}
