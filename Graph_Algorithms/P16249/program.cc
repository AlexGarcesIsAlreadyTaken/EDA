#include <iostream>
#include <queue>
#include <map>
using namespace std;

typedef string tasca;
typedef vector<tasca> successors;
typedef map<tasca, successors> digraf;

void top_sort(vector<tasca>& V, digraf& G) {
	map<tasca, int> pred;
	for (auto it = G.begin(); it != G.end(); ++it) {
		pred.insert(make_pair(it->first, 0));
	}
	for (auto it = G.begin(); it != G.end(); ++it) {
		for (int i = 0; i < it->second.size(); ++i) {
			tasca w = it->second[i];
			++pred[w];
		}
	}

	priority_queue<tasca, vector<tasca>, greater<tasca>> Q;
	for (auto it = pred.begin(); it != pred.end(); ++it) {
		if (it->second == 0) Q.push(it->first);
	}

	while (not Q.empty()) {
		tasca v = Q.top();
		Q.pop();
		for (int i = 0; i < G[v].size(); ++i) {
			tasca w = G[v][i];
			--pred[w];
			if (pred[w] == 0) Q.push(w);
		}
		V.push_back(v);
	}
}

int main() {
	int n;
	while (cin >> n) {
		digraf G;
		while (G.size() < n) {
			tasca c; cin >> c;
			G.insert(make_pair(c, successors(0)));
		}
		int m; cin >> m;
		for (int i = 0; i < m; ++i) {
			tasca x, y; cin >> x >> y;
			G[x].push_back(y);
		}
		vector<tasca> res;
		top_sort(res, G);
		if (res.size() < n) cout << "NO VALID ORDERING";
		else for (int i = 0; i < n; ++i) cout << res[i];
		cout << endl;

	}
}
