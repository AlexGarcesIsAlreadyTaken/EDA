#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> fila;
typedef vector<fila> matriu;

bool dfs(matriu& mapa, int x, int y) {
	if (mapa[x][y] == 't') return true;
	if (mapa[x][y] == 'X') return false;
	mapa[x][y] = 'X';
	return dfs(mapa, x, y+1) or dfs(mapa, x, y-1) or dfs(mapa, x+1, y) or dfs(mapa, x-1, y);
	
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
	if (dfs(mapa, f, c)) cout << "yes" << endl;
	else cout << "no" << endl;
}
