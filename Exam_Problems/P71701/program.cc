#include <iostream>
#include <vector>
using namespace std;

typedef vector<bool> VB;
typedef vector<char> VC;
typedef vector<VC> VVC;

void pinta(const VVC& tauler) {
	int n = tauler.size()-1;
	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < n; ++j) cout << tauler[i][j];
		cout << endl;
	}
	cout << "----------" << endl;
}

// u_f: fila de l'ultim rei colocat
// u_c: columna de l'ultim rei colocat
void e_s(VVC& tauler, int r, int k, int u_f, int u_c) {
	if (k == r) {pinta(tauler); return;}

	int n = tauler.size()-1;
	for (int i = u_f; i < n; ++i) {
		for (int j = 1; j < n; ++j) {
			if (i == u_f and j == 1) j = u_c;

			if (tauler[i+1][j] == 'K') continue;
			if (tauler[i-1][j] == 'K') continue;
			if (tauler[i][j+1] == 'K') continue;
			if (tauler[i][j-1] == 'K') continue;
			if (tauler[i+1][j+1] == 'K') continue;
			if (tauler[i+1][j-1] == 'K') continue;
			if (tauler[i-1][j+1] == 'K') continue;
			if (tauler[i-1][j-1] == 'K') continue;

			tauler[i][j] = 'K';
			int aux_u_f = i; if (j == n-1) aux_u_f = i+1;
			int aux_u_c = j+1; if (aux_u_f > i) aux_u_c = 1;
			e_s(tauler, r, k+1, aux_u_f, aux_u_c);
			tauler[i][j] = '.';

		}
	}
}

int main() {
	int n, r;
	cin >> n >> r;
	
	VVC tauler(n+2, VC(n+2, '.'));
	e_s(tauler, r, 0, 1, 1);
}



/*
 *		/////////
 *		/	.	.	.	/
 *		/	.	.	.	/
 *		/	.	.	.	/
 *		/////////
 *
 *
 *
 *
 *
 */
