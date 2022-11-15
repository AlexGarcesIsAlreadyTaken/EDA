#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define INF 1e8

typedef pair<int, int> vertex;
typedef vector<vertex> successors;
typedef vector<successors> digraf;

void resol(const vector<int>& pare, vector<int>& cami, int ini, int fi) {
	if (ini == fi) cami.push_back(ini);
	else {
		int v = pare[fi];
		resol(pare, cami, ini, v);
		cami.push_back(fi);
	}
}

int dijkstra(const digraf& G, vector<int>& cami , int x, int y) {
	int n = G.size();
	vector<int> D(n, INF);
	D[x] = 0;
	priority_queue<vertex, vector<vertex>, greater<vertex> > Q;
	Q.push(make_pair(D[x], x));
	vector<bool> visitat(n, false);
	vector<int> pare(n, -1);
	while (not Q.empty()) {
		int v = Q.top().second; Q.pop();
		//cout << v << endl;
		if (not visitat[v]) {
			visitat[v] = true;
			for (vertex w : G[v]) {
				//cout << "	" << v << " -> " << w.first << endl;
				int d = D[v] + w.second;
				if (D[w.first] > d) {
					D[w.first] = d;
					pare[w.first] = v;
				}
				Q.push(make_pair(D[w.first], w.first));
			}
		}
	}
	if (D[y] == INF) return -1;
	resol(pare, cami, x, y);
	return D[y];
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		digraf G(n);
		for (int i = 0; i < m; ++i) {
			int v; vertex w;
			cin >> v >> w.first >> w.second;
			//cout << v << " -> " << w.first << " cost: " << w.second << endl;
			G[v].push_back(w);
		}
		int x, y;
		cin >> x >> y;
		vector<int> cami;
		int res = dijkstra(G, cami, x, y);
		if (res == -1) cout << "no path from " << x << " to " << y;
		else for (int i = 0; i < cami.size(); ++i) {
			if (i > 0) cout << ' ';
			cout << cami[i];
		}
		cout << endl;
	}

}
