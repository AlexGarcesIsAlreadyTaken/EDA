#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> fila;
typedef vector<fila> matriu;

int dfs(matriu& mapa, int x, int y) {
	int tresor = 0;
	if (mapa[x][y] == 't') tresor = 1;
	if (mapa[x][y] == 'X') return 0;
	mapa[x][y] = 'X';
	return tresor + dfs(mapa, x, y+1) + dfs(mapa, x, y-1) + dfs(mapa, x+1, y) + dfs(mapa, x-1, y);
	
}

int main() {
	int n, m;
	cin >> n >> m;
	matriu mapa(n+2, fila(m+2, 'X'));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> mapa[i][j];
	int f, c;
	cin >> f >> c;
	cout << dfs(mapa, f, c) << endl;
}
