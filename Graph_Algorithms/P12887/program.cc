#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> vertex;
typedef vector<vertex> adjacents;
typedef vector<adjacents> graf;

typedef priority_queue<vertex, vector<vertex>, greater<vertex> > candidats;

int prim_algorithm(const graf& G) {
	int n  = G.size();
	vector<bool> visitat(n, false);
	visitat[1] = true;
	candidats Q;
	for (vertex u : G[1]) Q.push(u);
	int A = 1;
	int sum_w = 0;
	--n;
	while (A != n) {
		int v = Q.top().second;
		int w = Q.top().first;
		Q.pop();
		if (not visitat[v]) {
			//cout << v << ", w: " << w << endl;
			visitat[v] = true;
			for (vertex u : G[v]) {
				Q.push(u);
			//	cout << "	" << v << " -> " << u.second << endl;
			}
			sum_w += w;
			++A;
		}
	}
	return sum_w;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		graf G(n+1, adjacents(0));
		for (int i = 0; i < m; ++i) {
			int u, v, w;
			cin >> u >> v >> w;
			G[u].push_back(make_pair(w, v));
			G[v].push_back(make_pair(w, u));
			//cout << u << " <-> " << v << " weight: " << w << endl;
		}
		int pes_MST = prim_algorithm(G);
		cout << pes_MST << endl;
	}

}
