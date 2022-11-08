#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> vertex;
typedef pair<vertex, int> node;
typedef vector<char> fila;
typedef vector<fila> graf;

int dist_min(graf& G, int num_tresors, int x, int y) {
	if (G[x][y] == 'X') return -1;
	queue<node> Q;
	Q.push(make_pair(make_pair(x, y), 0)); //Punt de partida
	int max_dist = -1;
	while (not Q.empty()) {
		node v = Q.front(); Q.pop();
		int i = v.first.first;
		int j = v.first.second;
		int dist = v.second;
		if (G[i][j] == 't') {
			max_dist = dist;
			--num_tresors;
			if (num_tresors == 0) return max_dist;
		}
		G[i][j] = 'X';
		if (G[i+1][j] != 'X')
			Q.push(make_pair(make_pair(i+1, j), dist+1));
		if (G[i-1][j] != 'X')
			Q.push(make_pair(make_pair(i-1, j), dist+1));
		if (G[i][j+1] != 'X')
			Q.push(make_pair(make_pair(i, j+1), dist+1));
		if (G[i][j-1] != 'X')
			Q.push(make_pair(make_pair(i, j-1), dist+1));
	}
	return max_dist;
}

int main() {
	int n, m; cin >> n >> m;
	graf mapa(n+2, fila(m+2));
	int num_trofeus = 0;
	for (int i = 0; i < n+2; ++i) {
		for (int j = 0; j < m+2; ++j) {
			if (i == 0 or i == n+1 or j == 0 or j == m+1) mapa[i][j] = 'X';
			else cin >> mapa[i][j];
			if (mapa[i][j] == 't') ++num_trofeus;
		}
	}
	/*for (int i = 0; i < n+2; ++i) {
		for (int j = 0; j < m+2; ++j) {
			cout << mapa[i][j];
		}
		cout << endl;
	}*/
	int x, y; cin >> x >> y;
	int res = dist_min(mapa, num_trofeus, x, y);
	if (res != -1) cout << "distancia maxima: " << res << endl;
	else cout << "no es pot arribar a cap tresor" << endl;
}
