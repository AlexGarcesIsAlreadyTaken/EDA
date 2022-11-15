#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 1e8

typedef	pair<int, int> vertex;
typedef vector<vertex> successors;
typedef vector<successors> digraf;

typedef priority_queue<vertex, vector<vertex>, greater<vertex> > cua;

int dijkstra(const digraf& G, vector<int>& salts, int x, int y) {
	int n = G.size();
	vector<int> D(n, INF);
	D[x] = 0;
	salts[x] = 0;
	cua Q; Q.push(make_pair(D[x], x));
	vector<bool> visitat(n, false);
	while (not Q.empty()) {
		int v = Q.top().second; Q.pop();
		if (not visitat[v]) {
			visitat[v] = true;
			//cout << v << endl;
			for (vertex w : G[v]) {
				//cout << "	" << v << " -> " << w.first << "cost: " << w.second << endl;
				int d = D[v] + w.second;
				if (D[w.first] > d or (D[w.first] == d and salts[w.first] > salts[v]+1)) {
					//cout << "	" << w.first << " modificat" << endl;
					D[w.first] = d;
					salts[w.first] = salts[v] + 1;
					Q.push(make_pair(D[w.first], w.first));
				}
			}
		}
	}
	return D[y];
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		digraf G(n);
		for (int i = 0; i < m; ++i) {
			int u; vertex v;
			cin >> u >> v.first >> v.second;
			G[u].push_back(v);
			//cout << u << " -> " << v.first << " cost: " << v.second << endl;
		}
		int x, y; cin >> x >>  y;
		vector<int> salts(n, INF);
		int cost_min = dijkstra(G, salts, x, y);
		if (cost_min == INF) cout << "no path from " << x << " to " << y << endl;
		else cout << "cost " << cost_min << ", " << salts[y] << " step(s)" << endl;
	}
}
