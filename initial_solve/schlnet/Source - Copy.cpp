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

int N, subA, subB;
vector<vector<int>> paths;
vector<vector<int>> alteredPaths;

vector<int> bT, eT; // begin times and end times of nodes in dfs
vector<int> bT2, eT2;

void visit(int v, int& time, vector<int>& parents, vector<int>& states) {
	time++;
	bT[v] = time;
	states[v] = 0;
	for (int i = 0; i < paths[v].size(); i++) {
		if (states[paths[v][i]] == -1) {
			parents[paths[v][i]] = v;
			visit(paths[v][i], time, parents, states);
		}
	}
	states[v] = 1;
	time++;
	eT[v] = time;
}

void visit2(int v, int& time, vector<int>& parents, vector<int>& states) {
	time++;
	bT2[v] = time;
	states[v] = 0;
	for (int i = 0; i < alteredPaths[v].size(); i++) {
		if (states[alteredPaths[v][i]] == -1) {
			parents[alteredPaths[v][i]] = v;
			visit2(alteredPaths[v][i], time, parents, states);
		}
	}
	states[v] = 1;
	time++;
	eT2[v] = time;
}

void setNewPaths() {
	alteredPaths.resize(N);
	for (int i = 0; i < paths.size(); i++) {
		for (int j = 0; j < paths[i].size(); j++) {
			alteredPaths[paths[i][j]].push_back(i);
		}
	}
}

vector<int> orderNodes() {
	vector<int> ordered(N);
	for (int i = 0; i < N; i++) {
		ordered[i] = i;
	}
	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			if (eT[ordered[i]] < eT[ordered[j]]) {
				int tmp = ordered[i];
				ordered[i] = ordered[j];
				ordered[j] = tmp;
			}
		}
	}
	return ordered;
}

vector<vector<int>> recreatePaths(vector<int>& b, vector<int>& e, vector<vector<int>>& useP) {
	vector<vector<int>> startingPaths = useP;
	vector<vector<int>> newPaths;
	vector<vector<int>> forest(N);
	for (int i = 0; i < N; i++) { // find SCCs
		for (int j = 0; j < N; j++) {
			if (b[i] > b[j] && e[i] < e[j]) {
				forest[j].push_back(i);
			}
			if (b[i] < b[j] && e[i] > e[j]) {
				forest[i].push_back(j);
			}
		}
	}
	vector<vector<int>> allSCC;
	vector<bool> visited(N, false);
	queue<int> toVisit;
	int node = 0;
	for (int i = 0; i < N; i++) {
		if (visited[i]) {
			continue;
		}
		vector<int> SCC;
		int n = i;
		toVisit.push(n);
		while (!toVisit.empty()) {
			n = toVisit.front();
			toVisit.pop();
			if (visited[n]) {
				continue;
			}
			visited[n] = true;
			SCC.push_back(n);
			for (int j = 0; j < forest[n].size(); j++) {
				if (!visited[forest[n][j]]) {
					toVisit.push(forest[n][j]);
				}
			}
		}

		for (int j = 0; j < N; j++) {
			for (int k = 0; k < startingPaths[j].size(); k++) {
				bool replaced = false;
				for (int l = 0; l < SCC.size(); l++) {
					if (SCC[l] == startingPaths[j][k]) {
						startingPaths[j][k] = node;
					}
				}
			}
		}
		allSCC.push_back(SCC);
		node++;
	}

	for (int i = 0; i < allSCC.size(); i++) {
		vector<bool> added(N, false);
		vector<int> newPath;
		for (int j = 0; j < allSCC[i].size(); j++) {
			added[allSCC[i][j]] = true;
		}
		for (int j = 0; j < allSCC[i].size(); j++) {
			for (int k = 0; k < startingPaths[allSCC[i][j]].size(); k++) {
				int node = startingPaths[allSCC[i][j]][k];
				if (!added[node]) {
					newPath.push_back(node);
					added[node] = true;
				}
			}
		}
		newPaths.push_back(newPath);
	}
	return newPaths;
}

int findStarts(vector<vector<int>>& p) { // find number of nodes with in-degree of 0 in p
	int starts = 0;
	for (int i = 0; i < p.size(); i++) {
		bool found = false;
		for (int j = 0; j < p.size(); j++) {
			if (j == i) {
				continue;
			}
			for (int k = 0; k < p[j].size(); k++) {
				if (p[j][k] == i) {
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}
		if (!found) {
			starts++;
		}
	}
	return starts;
}

void findAns() {
	bT.resize(N);
	bT2.resize(N);
	eT.resize(N);
	eT2.resize(N);
	vector<int> parents(N, -1);
	vector<int> states(N, -1);
	int time = 0;

	for (int i = 0; i < N; i++) {
		if (states[i] == -1) {
			visit(i, time, parents, states);
		}
	}

	vector<vector<int>> original = recreatePaths(bT, eT, paths);
	subA = findStarts(original);

	setNewPaths();
	vector<int> order = orderNodes();

	time = 0;
	parents.clear();
	states.clear();
	parents.resize(N, -1);
	states.resize(N, -1);
	for (int i = 0; i < N; i++) {
		if (states[order[i]] == -1) {
			visit2(order[i], time, parents, states);
		}
	}

	vector<vector<int>> newP = recreatePaths(bT2, eT2, alteredPaths);
	int startNodes;
	if (newP.size() == 1) {
		subB = 0;
		return;
	}
	startNodes = findStarts(newP); // num of nodes with in-degree of 0

	for (int i = 0; i < newP.size(); i++) {
		if (newP[i].size() == 0) {
			subB++; // nodes with out-degree of 0
		}
	}
	if (subB < startNodes) {
		subB = startNodes;
	}
}

int main() {
	ifstream fin("schlnet.in");
	fin >> N;
	paths.resize(N);
	for (int i = 0; i < N; i++) {
		int r;
		fin >> r;
		while (r != 0) {
			paths[i].push_back(r - 1);
			fin >> r;
		}
	}

	findAns();

	ofstream fout("schlnet.out");
	fout << subA << '\n' << subB << '\n';
}