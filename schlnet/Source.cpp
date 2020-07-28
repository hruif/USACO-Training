/*
ID: ruifanl1
TASK: schlnet
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
	int d; // discovery time
	int f; // finish time
	int p; // parent
	char color; // state of node
};

int N;
vector<Node> V, Vt;
vector<vector<int>> E, Et;

void DFSVisit(vector<Node>& V, vector<vector<int>>& E, int u, int& time) {
	time++;
	V[u].d = time;
	V[u].color = 'g';
	for (int i = 0; i < E[u].size(); i++) {
		int v = E[u][i];
		if (V[v].color == 'w') {
			V[v].p = u;
			DFSVisit(V, E, v, time);
		}
	}
	V[u].color = 'b';
	time++;
	V[u].f = time;
}

void DFS(vector<Node>& V, vector<vector<int>>& E, vector<int>& order) {
	int n = E.size();
	for (int i = 0; i < n; i++) {
		V[i].color = 'w';
		V[i].p = -1;
	}
	int time = 0;
	for (int i = 0; i < n; i++) {
		int l = order[i];
		if (V[l].color == 'w') {
			DFSVisit(V, E, l, time);
		}
	}
}

void transpose(vector<Node>& V, vector<vector<int>>& E, vector<Node>& Vt, vector<vector<int>>& Et) {
	for (int i = 0; i < E.size(); i++) {
		for (int j = 0; j < E[i].size(); j++) {
			Et[E[i][j]].push_back(i);
		}
	}
}

void getGp(vector<Node>& V, vector<vector<int>>& E, vector<vector<int>>& Ep) {
	for (int i = 0; i < V.size(); i++) {
		if (V[i].p == -1) {
			continue;
		}
		Ep[V[i].p].push_back(i);
	}
}

void DFSSimple(vector<Node>& V, vector<vector<int>>& E, int s, vector<int>& list) {
	list.push_back(s);
	for (int i = 0; i < E[s].size(); i++) {
		DFSSimple(V, E, E[s][i], list);
	}
}

void contractSCC(vector<Node>& V, vector<vector<int>>& E, vector<Node>& Vt, vector<vector<int>>& Et, vector<Node>& Vc, vector<vector<int>>& Ec, vector<vector<int>>& EcIn) {
	vector<vector<int>> sccs;
	vector<int> sccIndex(N);
	vector<vector<int>> Ep(N);
	getGp(Vt, Et, Ep);
	for (int i = 0; i < N; i++) {
		if (Vt[i].p != -1) {
			continue;
		}
		vector<int> list;
		DFSSimple(Vt, Ep, i, list);
		int index = sccs.size();
		for (int j = 0; j < list.size(); j++) {
			sccIndex[list[j]] = index;
		}
		sccs.push_back(list);
	}

	Vc.resize(sccs.size());
	Ec.resize(sccs.size());
	EcIn.resize(sccs.size());
	for (int i = 0; i < sccs.size(); i++) {
		vector<bool> flags(sccs.size(), false);
		for (int k = 0; k < sccs[i].size(); k++) {
			int a = sccs[i][k];
			for (int j = 0; j < E[a].size(); j++) {
				int otherNodeIndex = E[a][j];
				int otherNodeSCCIndex = sccIndex[otherNodeIndex];
				if (i == otherNodeSCCIndex) {
					continue;
				}
				if (flags[otherNodeSCCIndex]) {
					continue;
				}
				flags[otherNodeSCCIndex] = true;
				Ec[i].push_back(otherNodeSCCIndex);
				EcIn[otherNodeSCCIndex].push_back(i);
			}
		}
	}
}

void SCC(vector<Node>& V, vector<vector<int>>& E, vector<Node>& Vt, vector<vector<int>>& Et) {
	vector<int> order(N);
	for (int i = 0; i < N; i++) {
		order[i] = i;
	}
	
	DFS(V, E, order);
	transpose(V, E, Vt, Et);

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			if (V[order[i]].f < V[order[j]].f) {
				int t = order[i];
				order[i] = order[j];
				order[j] = t;
			}
		}
	}

	DFS(Vt, Et, order);
}

int main() {
	ifstream fin("schlnet.in");
	fin >> N;
	E.resize(N);
	Et.resize(N);
	V.resize(N);
	Vt.resize(N);
	for (int i = 0; i < N; i++) {
		int t;
		fin >> t;
		while (t != 0) {
			E[i].push_back(t - 1);
			fin >> t;
		}
	}
	SCC(V, E, Vt, Et);

	vector<Node> Vc;
	vector<vector<int>> Ec, EcIn;
	contractSCC(V, E, Vt, Et, Vc, Ec, EcIn);

	int inDegree = 0, outDegree = 0;
	for (int i = 0; i < Vc.size(); i++) {
		if (Ec[i].size() == 0) {
			outDegree++;
		}
		if (EcIn[i].size() == 0) {
			inDegree++;
		}
	}

	int B = max(inDegree, outDegree);
	if (Vc.size() == 1) {
		B = 0;
	}

	ofstream fout("schlnet.out");
	fout << inDegree << '\n' << B << '\n';
}