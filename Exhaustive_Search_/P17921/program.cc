#include <iostream>
#include <vector>
using namespace std;

typedef vector<bool> fila;
typedef vector<fila> matriu;

void escriu(const matriu& M) {
	int n = M.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) cout << (M[i][j] == true ? 'Q' : '.');
		cout << endl;
	}
	cout << endl;
}

bool pos_valida(vector<int>& pos, int fila, int i) {
	for (int j = 0; j < fila; ++j) {
		if (pos[j] - j == i - fila) return false;
		if (pos[j] + j == i + fila) return false;
	}
	return true;
}

void n_reines(vector<bool>& reina, vector<int>& pos, matriu& M, int fila) {
	int n = M.size();
	if (fila == n) escriu(M);
	else {
		for (int i = 0; i < n; ++i)
			if (not reina[i] and pos_valida(pos, fila, i)) {
				reina[i] = true;
				M[fila][i] = true;
				pos[fila] = i; n_reines(reina, pos, M, fila+1);
				M[fila][i] = false;
				reina[i] = false;
			}
	}
}

int main() {
	int n;
	cin >> n;
	matriu tauler(n, fila(n,  false));
	vector<int> pos(n);
	vector<bool> reina(n, false);
	n_reines(reina, pos, tauler, 0);

}
