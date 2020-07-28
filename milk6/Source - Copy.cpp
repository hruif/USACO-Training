/*
ID: ruifanl1
TASK: milk6
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> costs, connected; // cost of path i
vector<vector<int>> paths, pathsFrom; // S to E - from index S to which Es
queue<vector<int>> removed; // BFS search which paths to remove

bool isPath(vector<vector<int>>& pf) {
	int start = 0;
	int end = N - 1;
	int total = 0;
	vector<int> flow(N, -1);
	vector<bool> visited(N, false);
	flow[0] = INT_MAX;
	int max = 0;
	int index = -1;

	while (true) {
		max = -1;
		index = -1;
		for (int i = 0; i < N; i++) {
			if ((flow[i] > max || max == -1) && !visited[i]) {
				max = flow[i];
				index = i;
			}
		}
		if (index == -1 || index == N - 1) {
			break;
		}
		visited[index] = true;
		for (int i = 0; i < pf[index].size(); i++) {
			flow[pf[index][i]] = 1;
		}
	}
	if (index == -1) {
		return true;
	}
	if (index == end) {
		return false;
	}
}

void removePath(int path, vector<vector<int>>& pf) {
	int n1 = paths[path][0];
	int n2 = paths[path][1];
	for (int i = 0; i < pf[n1].size(); i++) {
		if (pf[n1][i] == n2) {
			pf[n1].erase(pf[n1].begin() + i);
			break;
		}
	}
	for (int i = 0; i < pf[n2].size(); i++) {
		if (pf[n2][i] == n1) {
			pf[n2].erase(pf[n2].begin() + i);
			break;
		}
	}
}

int findCost(int path) {
	int n1 = paths[path][0];
	int n2 = paths[path][1];
	return costs[n1][n2];
}

bool isBetter(vector<int>& original, vector<int>& next) {
	int len1 = original.size();
	int len2 = next.size();
	if (len1 < len2) {
		return false;
	}
	if (len1 > len2) {
		return true;
	}
	for (int i = 0; i < len1; i++) {
		if (original[i] < next[i]) {
			return false;
		}
		if (original[i] > next[i]) {
			return true;
		}
	}
	return false;
}

int main() {
	ifstream fin("milk6.in");
	fin >> N >> M;
	connected.resize(N, vector<int>(N, 0));
	costs.resize(N, vector<int>(N, 0));
	pathsFrom.resize(N);
	for (int i = 0; i < N; i++) {
		int S, E, C;
		fin >> S >> E >> C;
		S--;
		E--;
		connected[S][E] = 1;
		connected[E][S] = 1;
		costs[S][E] = C;
		costs[E][S] = C;
		vector<int> path;
		path.push_back(S);
		path.push_back(E);
		paths.push_back(path);
		pathsFrom[S].push_back(E);
		pathsFrom[E].push_back(S);
	}

	int bestCost = -1;
	vector<bool> beenRemoved(M, false);
	vector<int> ans;
	vector<int> tmp;
	removed.push(tmp);
	while (!removed.empty()) {
		vector<vector<int>> newPF = pathsFrom;
		for (int i = 0; i < removed.front().size(); i++) {
			removePath(removed.front()[i], newPF);
		}
		if (!isPath(newPF)) {
			int cost = 0;
			for (int i = 0; i < removed.front().size(); i++) {
				cost += findCost(removed.front()[i]);
			}
			if (cost < bestCost || bestCost) {
				bestCost = cost;
				ans = removed.front();
			}
			else if (cost == bestCost && isBetter(ans, removed.front())) {
				ans = removed.front();
			}
		}
		else {
			for (int i = 0; i < removed.front().size(); i++) {
				beenRemoved[removed.front()[i]] = true;
			}
			for (int i = 0; i < M; i++) {
				if (!beenRemoved[i]) {
					removed.front().push_back(i);
					removed.push(removed.front());
					removed.front().pop_back();
				}
			}
		}
		removed.pop();
	}

	ofstream fout("milk6.out");
	int ansLen = ans.size();
	fout << bestCost << ' ' << ansLen<< '\n';
	for (int i = 0; i < ansLen; i++) {
		fout << ans[i] << '\n';
	}
}