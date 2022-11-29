#include <iostream>
#include <vector>
using namespace std;

bool pos_valida(const vector<int>& pos, int fila, int i) {
	for (int j = 0; j < fila; ++j) {
		//if (pos[j] == i) return false;	//esta en vertical
		if (pos[j] - j == i - fila) return false;	//Diagonal principal
		if (pos[j] + j == i + fila) return false;
	}
	return true;
}

int solucions_valides(vector<bool>& col, vector<int>& posicions, int fila) {
	int n = posicions.size();
	int res = 0;
	for (int i = 0; i < n; ++i) {
		if (not col[i] and pos_valida(posicions, fila, i)) {
			posicions[fila] = i;
			col[i] = true;
			if (fila == n-1) res += 1;
			else res += solucions_valides(col, posicions, fila+1);
			col[i] = false;
		}
	}
	return res;

}

int main() {
	int n; cin >> n;
	vector<int> posicions(n);
	vector<bool> col(n, false);
	int res = solucions_valides(col, posicions, 0);
	cout << res << endl;
}
