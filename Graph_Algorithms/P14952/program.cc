#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef int vertex;
typedef vector<vertex> successors;
typedef vector<successors> digraf;

void top_sort(vector<vertex>& V, const digraf& G) {
	vector<int> pred(G.size());
	for (int v = 0; v < G.size(); ++v) {
		for (vertex w : G[v]) ++pred[w];
	}

	priority_queue<vertex, vector<vertex>, greater<vertex>> Q;
	for (int v = 0; v < G.size(); ++v) {
		if (pred[v] == 0) Q.push(v);
	}

	while (not Q.empty()) {
		vertex v = Q.top();
		Q.pop();
		for (vertex w : G[v]) {
			--pred[w];
			if (pred[w] == 0) Q.push(w);
		}
		V.push_back(v);
	}
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		digraf G(n, successors(0));
		for (int i = 0; i < m; ++i) {
			int x, y;
			cin >> x >> y;
			G[x].push_back(y);
		}

		vector<vertex> result;
		top_sort(result, G);
		for (int i = 0; i < result.size(); ++i) {
			if (i > 0) cout << ' ';
			cout << result[i];
		}
		cout << endl;
	}
}
