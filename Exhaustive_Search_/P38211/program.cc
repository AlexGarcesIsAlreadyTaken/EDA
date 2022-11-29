#include <iostream>
#include <vector>
using namespace std;

typedef vector<bool> fila;
typedef vector<fila> matriu;
typedef vector<bool> marcador;

void escriu(const matriu& M) {
	int n = M.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) cout << (M[i][j] == true ? 'Q' : '.');
		cout << endl;
	}
}

bool n_reines(marcador& col, marcador& DP, marcador& DS, vector<int>& pos, matriu& M, int fila) {
	int n = M.size();
	if (fila == n) {
		escriu(M);
		return true;
	}
	else {
		for (int i = 0; i < n; ++i)
			if (not col[i] and not DP[i+fila] and not DS[i-fila+n-1]) {
				col[i] = true;
				DP[i+fila] = true;
				DS[i-fila+n-1] = true;
				M[fila][i] = true;
				pos[fila] = i; 
				if (n_reines(col, DP, DS, pos, M, fila+1)) return true;
				M[fila][i] = false;
				DS[i-fila+n-1] = false;
				DP[i+fila] = false;
				col[i] = false;
			}
		return false;
	}
}

int main() {
	int n;
	cin >> n;
	matriu tauler(n, fila(n,  false));
	vector<int> pos(n);
	marcador col(n, false);
	marcador DP(2*n - 1, false);
	marcador DS(2*n - 1, false);
	if (not n_reines(col, DP, DS, pos, tauler, 0)) cout << "NO SOLUTION" << endl;

}
