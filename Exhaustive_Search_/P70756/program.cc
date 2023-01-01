#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<VS> VVS;

void imprimeix(const VVS& S, const VI& P_S) {
	for (int i = 0; i < P_S.size(); ++i) {
		cout << "subconjunt " << i+1 << ": {";
		for (int j = 0; j < P_S[i]; ++j) {
			if (j != 0) cout << ',';
			cout << S[i][j];
		}
		cout << '}' << endl;
	}
	cout << endl;
}

void particiona(const VS& paraules, VVS& subconjunts, VI& paraules_subconjunt, int i) {
	int n = paraules.size();
	if (i > n) return;
	if (n == i) {imprimeix(subconjunts, paraules_subconjunt); return;}

	for (int j = 0; j < subconjunts.size(); ++j) {
		int aux = paraules_subconjunt[j];
		subconjunts[j][aux] = paraules[i];
		++paraules_subconjunt[j];
		particiona(paraules, subconjunts, paraules_subconjunt, i+1);
		--paraules_subconjunt[j];
	}
}

int main() {
	int n; cin >> n;
	VS paraules(n);
	for (int i = 0; i < n; ++i) cin >> paraules[i];
	int p; cin >> p;
	VI paraules_subconjunt(p, 0);
	VVS subconjunts(p, VS(n, ""));
	particiona(paraules, subconjunts, paraules_subconjunt, 0);
}
