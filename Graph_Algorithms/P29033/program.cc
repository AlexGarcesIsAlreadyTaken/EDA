#include <iostream>
#include <vector>
using namespace std;

typedef int vertex;
typedef vector<vertex> llista_adj;
typedef vector<llista_adj> graf;

bool dos_colorejable(const graf& G, vector<bool>& visitat, vector<char>& color, vertex v) {
	visitat[v] = true;
	/*if (color[v] == 'i')  //Primerissim cop que es visita el graf
		color[v] = 'b';
	*/
	char contrari_v = (color[v] == 'b') ? 'v' : 'b'; 
	
	for (vertex w: G[v]) {
		if (color[w] == 'i') color[w] = contrari_v;
		else if (color[w] == color[v]) return false;
		if (not visitat[w] and not dos_colorejable(G, visitat, color, w)) return false;
	}
	
	return true;
}

bool dos_colorejable(const graf& G) {

	/* i = color indeterminat
	   b = color blau
	   v = color vermell
	*/
	vector<char> color(G.size(), 'i');
	vector<bool> visitat(G.size(), false);
	color[0] = 'b';
	for (int v = 0; v < G.size(); ++v) {
		if (not visitat[v] and not dos_colorejable(G, visitat, color, v)) return false;
	}
	return true;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		graf G(n, llista_adj(0));
		for (int i = 0; i < m; ++i) {
			vertex x, y;
			cin >> x >> y;
			G[x].push_back(y);
			G[y].push_back(x);
		}
		if (dos_colorejable(G)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
}
