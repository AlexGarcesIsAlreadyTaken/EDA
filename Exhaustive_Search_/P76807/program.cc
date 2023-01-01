#include <vector>
#include <iostream>
using namespace std;

typedef vector<bool> VB;
typedef vector<VB> VVB;

typedef vector<char> VC;
typedef vector<VC> VVC;

void mostra(const VVC& sudoku) {
	cout << endl;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (j != 0) cout << ' ';
			cout << sudoku[i][j];
		}
		cout << endl;
	}
}

//s: nombres resolts
bool resol(VVC& sudoku, VVB& rows, VVB& cols, VVB& cells, int s) {
	if (s > 9*9) return false;
	if (s == 9*9) {mostra(sudoku); return true;}

	int i = s/9; int j = s%9;
	
	if (sudoku[i][j] != '.') return resol(sudoku, rows, cols, cells, s+1);
	
	int aux = i/3;
	for (char k = '1'; k <= '9'; ++k) {
		int m = k - '1';
		if (rows[i][m]) continue;
		if (cols[j][m]) continue;
		if (cells[j/3 + aux*3][m]) continue;


		rows[i][m] = true;
		cols[j][m] = true;
		cells[j/3 + aux*3][m] = true;
		
		sudoku[i][j] = k;
		if (resol(sudoku, rows, cols, cells, s+1)) return true;
		sudoku[i][j] = '.';
		
		rows[i][m] = false;
		cols[j][m] = false;
		cells[j/3 + aux*3][m] = false;
	}
	return false;
}

int main() {
	int n; cin >> n; cout << n << endl;
	while (n > 0) {
		VVB cells(9, VB(9, false));
		VVB rows(9, VB(9, false));
		VVB cols(9, VB(9, false));

		VVC sudoku(9, VC(9));
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				char c; cin >> c;
				sudoku[i][j] = c;
				if (c != '.') {
					int m = c - '1';
					rows[i][m] = true;
					cols[j][m] = true;
					int aux = i/3;
					cells[j/3 + aux*3][m] = true;
		}	}	}

		resol(sudoku, rows, cols, cells, 0);

		--n;
	}
}
