#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

#define INF 1e8

typedef pair<int, int> node;
typedef vector<node> successors;
typedef vector<successors> digraf;


int dijkstra(const digraf& G, int x, int y) {
	int n = G.size();
	vector<int> D (n, INF); //Distancia de D[v] a x
	D[x] = 0;
	
	priority_queue<node, vector<node>, greater<node> > Q;
	Q.push(make_pair(D[x], x));
	vector<bool> visitats(n, false);
	while (not Q.empty()) {
		int v = Q.top().second; Q.pop();
		if (not visitats[v]) {
			for (node w : G[v]) {
				int d = D[v] + w.first;
				if (D[w.second] > d) D[w.second] = d;
				Q.push(make_pair(D[w.second], w.second));
			}
		}
		visitats[v] = true; 
	}
	return D[y];
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		digraf G(n);
		for (int v = 0; v < m; ++v) {
			int i;
			cin >> i;
			node j; cin >> j.second >> j.first;
			G[i].push_back(j);
		}
		int x, y; cin >> x >> y;
		int cami = dijkstra(G, x, y);
		if (cami != INF) cout << cami << endl;
		else cout << "no path from " << x << " to " << y << endl;
	}
}
