#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> vertex;
typedef pair<vertex, int> node;
typedef vector<char> fila;
typedef vector<fila> graf;

int dist_min(graf& G, int x, int y) {
	int n = G.size();
	int m = G[0].size();
	if (G[x][y] == 'X') return -1;
	queue<node> Q;
	Q.push(make_pair(make_pair(x, y), 0)); //Punt de partida
	int res = -1;
	if (G[x][y] == 't') res = 0;
	G[x][y] = 0;
	while (not Q.empty()) {
		node v = Q.front(); Q.pop();
		int i = v.first.first;
		int j = v.first.second;
		int dist = v.second;
		if (i+1 < n and G[i+1][j] != 'X') {
			Q.push(make_pair(make_pair(i+1, j), dist+1));
			if (G[i+1][j] == 't') res = dist+1;
			G[i+1][j] = 'X';
		}
		if (i-1 >= 0 and G[i-1][j] != 'X') {
			Q.push(make_pair(make_pair(i-1, j), dist+1));
			if (G[i-1][j] == 't') res = dist+1;
			G[i-1][j] = 'X';
		}
		if (j+1 < m and G[i][j+1] != 'X') {
			Q.push(make_pair(make_pair(i, j+1), dist+1));
			if (G[i][j+1] == 't') res = dist+1;
			G[i][j+1] = 'X';
		}
		if (j-1 >= 0 and G[i][j-1] != 'X') {
			Q.push(make_pair(make_pair(i, j-1), dist+1));
			if (G[i][j-1] == 't') res = dist+1;
			G[i][j-1] = 'X';
		}
	}
	return res;
}

int main() {
	int n, m; cin >> n >> m;
	graf mapa(n, fila(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> mapa[i][j];
		}
	}
	int x, y; cin >> x >> y;
	int res = dist_min(mapa, x-1, y-1);
	if (res != -1) cout << "distancia maxima: " << res << endl;
	else cout << "no es pot arribar a cap tresor" << endl;
}
