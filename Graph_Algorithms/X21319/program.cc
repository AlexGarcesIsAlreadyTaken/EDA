#include <iostream>
#include <unordered_map>
#include <map>
#include <queue>
using namespace std;

typedef string node;

#define AND 0
#define OR 1
#define NOT 2
#define INPUT -1

struct porta {
	int inp1, inp2;
	int tipus; // op = {AND, OR, NOT, INPUT}
	bool value;
};

//typedef unordered_map<node, pair<porta, successors> > digraf;

typedef vector<porta> portes;
typedef map<node, int> id;
typedef vector<int> successors;
typedef vector<successors> digraf;

void resol(const digraf& G, portes& PS) {
	vector<int> pred(G.size());
	for (int v = 0; v < G.size(); ++v) {
		for (int w = 0; w < G[v].size(); ++w) {
			pred[G[v][w]]++;
		}
	}
	queue<int> Q;
	for (int v = 0; v < G.size(); ++v) { 
		if (pred[v] == 0) Q.push(v);
		//cout << v << ' ' << pred[v] << endl;
	}

	while (not Q.empty()) {
		int v = Q.front(); Q.pop();	// v es a out
		for (int w = 0; w < G[v].size(); ++w) {
			//cout << v << " -> " << G[v][w] << endl;
			pred[G[v][w]]--;
			if (pred[G[v][w]] == 0) Q.push(G[v][w]);
		}
		int tipus_porta = PS[v].tipus;
		if (tipus_porta == AND) {
			int inp1 = PS[v].inp1;
			int inp2 = PS[v].inp2;
			PS[v].value = PS[inp1].value and PS[inp2].value;
			//cout << inp1 << "and" << inp2  << "->" << v <<": " << PS[v].value << endl;
		}
		else if (tipus_porta == OR) {
			int inp1 = PS[v].inp1;
			int inp2 = PS[v].inp2;
			PS[v].value = PS[inp1].value or PS[inp2].value;
			//cout << inp1 << "or" << inp2  << "->" << v <<": " << PS[v].value << endl;
		}
		else if (tipus_porta == NOT) {
			int inp = PS[v].inp1;
			PS[v].value = not PS[inp].value;
			//cout << inp << "not ->" << v << ": " << PS[v].value << endl;
		}
	}
}

void crea_id(id& ID, portes& PS, digraf& G, const node& nom, int& num_portes, const porta& p) {
	ID.insert(make_pair(nom, num_portes));
	++num_portes;
	G.push_back(successors(0));
	PS.push_back(p);
}

int main() {
	string op;
	vector<node> output;
	portes PS;
	id ID;
	digraf G;
	porta p;
	node nom;
	int num_portes = 0;
	int num_inputs = 0;
	while (cin >> op and op != "END") {
		if (op == "OUTPUT") {
			while (cin >> nom and nom != "END") {
				output.push_back(nom);
			}
		}
		else if (op == "INPUT") {
			while (cin >> nom and nom != "END") {
				p.tipus = INPUT;
				crea_id(ID, PS, G, nom, num_portes, p);
				++num_inputs;
			}
		}
		else if (op == "NOT") {
			cin >> nom;
			if (ID.find(nom) == ID.end()) {
				crea_id(ID, PS, G, nom, num_portes, p);
			}
			node input; cin >> input;
			if (ID.find(input) == ID.end()) {
				crea_id(ID, PS, G, input, num_portes, p);
			}
			int pred = ID[input];
			p.tipus = NOT;
			p.inp1 = pred;
			G[pred].push_back(ID[nom]);
			PS[ID[nom]] = p;
		}
		else {
			cin >> nom;
			if (ID.find(nom) == ID.end()) {
				crea_id(ID, PS, G, nom, num_portes, p);
			}
			
			node inp1, inp2; cin >> inp1 >> inp2;
			if (ID.find(inp1) == ID.end()) {
				crea_id(ID, PS, G, inp1, num_portes, p);
			}
			if (ID.find(inp2) == ID.end()) {
				crea_id(ID, PS, G, inp2, num_portes, p);
			}
			int pred = ID[inp1];
			p.inp1 = pred;
			G[pred].push_back(ID[nom]);
			pred = ID[inp2];
			p.inp2 = pred;
			G[pred].push_back(ID[nom]);
			p.tipus = op == "AND" ? AND : OR;
			PS[ID[nom]] = p;
		}
	}
	char val;
	while (cin >> val) {
		int inp = 0;
		PS[inp].value = val == 'T' ? true : false;
		for (int i = 1; i < num_inputs; ++i) {
			++inp;
			cin >> val;
			PS[inp].value = val == 'T' ? true : false;
		}
		resol(G, PS);
		for (int i = 0; i < output.size(); ++i) {
			if (i > 0) cout << ' ';
			node nom = output[i];
			int out = ID[nom];
			cout << (PS[out].value ? 'T' : 'F');
		}
		cout << endl;
	}
}
