#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct roca {
	int id;
	double x, y; //cord
	double radi; //radi
};

typedef vector<roca> graf;

bool less_than_d(const roca& a, const roca& b, const double& d) {
	double x = a.x-b.x;
	double y = a.y-b.y;
	double exc = a.radi + b.radi;
	//cout << a.id << " -> " << b.id << ": " << sqrt(x*x+y*y) - a.radi - b.radi << endl;
	return (x*x + y*y) <= (d*d + 2*d*exc + exc*exc);
}

int min_salts(graf& G, double d) {
	int n = G.size();
	vector<int> salts(n, 0);
	vector<bool> in_Q(n, false);
	queue<roca> Q;
	Q.push(G[0]);
	in_Q[0] = true;
	while (not Q.empty()) {
		roca r = Q.front(); Q.pop();
		for (int w = 0; w < n; ++w) {
			if (w != r.id and not in_Q[w] and less_than_d(r, G[w], d)) {
				if (w == n-1) return salts[r.id]+1;
				salts[w] = salts[r.id]+1;
				in_Q[w] = true;
				Q.push(G[w]);
			}
		}
	}
	return -1;
}

int main() {
	int n;
	while (cin >> n) {
		double d;
		cin >> d;
		graf G(n);
		for (int i = 0; i < n; ++i) {
			roca R;
			R.id = i;
			cin >> R.x >> R.y >> R.radi;
			G[i] = R;
		}
		int salts = min_salts(G, d);
		if (salts != -1) cout << salts << endl;
		else cout << "Xof!" << endl;
	}
}

