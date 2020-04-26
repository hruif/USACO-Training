/*
ID: ruifanl1
TASK: holstein
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int V, G;
queue<vector<int>> open;
vector<int> needed, solution;
vector<vector<int>> feeds;

bool isSolution(vector<int>& current) {
	if (current.empty()) {
		return false;
	}
	vector<int> sum(V);
	for (int i = 0; i < current.size(); i++) {
		for (int j = 0; j < V; j++) {
			sum[j] += feeds[current[i]][j];
		}
	}
	for (int i = 0; i < V; i++) {
		if (sum[i] < needed[i]) {
			return false;
		}
	}
	return true;
}

void bfs() {
	while (!open.empty()) {
		vector<int> current = open.front();
		open.pop();
		if (isSolution(current)) {
			solution = current;
			return;
		}
 		for (int i = current.empty() ? 0 : current.back() + 1; i < G; i++) {
			vector<int> child = current;
			child.push_back(i);
			open.push(child);
		}
	}
}

int main() {
	ifstream fin("holstein.in");
	fin >> V;
	for (int i = 0; i < V; i++) {
		int tmp;
		fin >> tmp;
		needed.push_back(tmp);
	}
	fin >> G;
	feeds.resize(G);
	for (int i = 0; i < G; i++) {
		feeds[i].resize(V);
		for (int j = 0; j < V; j++) {
			fin >> feeds[i][j];
		}
	}

	open.push(vector<int>());
	bfs();
	ofstream fout("holstein.out");
	int len = solution.size();
	fout << len;
	for (int i = 0; i < len; i++) {
		fout << ' ' << solution[i] + 1;
	}
	fout << '\n';
}