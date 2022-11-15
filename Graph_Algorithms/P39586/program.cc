#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 1e8

typedef	pair<int, int> vertex;
typedef vector<vertex> successors;
typedef vector<successors> digraf;

typedef priority_queue<vertex, vector<vertex>, greater<vertex> > cua;

int dijkstra(const digraf& G, vector<int>& camins, int x, int y) {
	int n = G.size();
	vector<int> D(n, INF);
	D[x] = 0;
	cua Q; Q.push(make_pair(D[x], x));
	vector<bool> visitat(n, false);
	camins[x] = 1;
	while (not Q.empty()) {
		int v = Q.top().second; Q.pop();
		if (not visitat[v]) {
			visitat[v] = true;
			//cout << v << endl;
			for (vertex w : G[v]) {
				//cout << "	" << v << " -> " << w.first << "cost: " << w.second << endl;
				int d = D[v] + w.second;
				if (D[w.first] > d) {
					//cout << "	" << w.first << " modificat" << endl;
					camins[w.first] = camins[v];
					D[w.first] = d;
					Q.push(make_pair(D[w.first], w.first));
				}
				else if (D[w.first] == d) camins[w.first] += camins[v];
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
		vector<int> camins(n, 0);
		int cost_min = dijkstra(G, camins, x, y);
		if (cost_min == INF) cout << "no path from " << x << " to " << y << endl;
		else cout << "cost " << cost_min << ", " << camins[y] << " way(s)" << endl;
	}
}
