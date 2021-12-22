/*
ID: ruifanl1
TASK: milk6
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>
#include <string.h>

using namespace std;

int N, M;
vector<vector<int>> connected;
vector<vector<int>> routes;
vector<vector<int>> paths;
vector<vector<int>> costs;

void sortRoutes() {
	for (int i = 0; i < M - 1; i++) {
		for (int j = i + 1; j < M; j++) {
			if (routes[i][2] < routes[j][2]) {
				vector<int> r = routes[i];
				routes[i] = routes[j];
				routes[j] = r;
			}
			if (routes[i][2] == routes[j][2]) {
				if (routes[i][3] > routes[j][3]) {
					vector<int> r = routes[i];
					routes[i] = routes[j];
					routes[j] = r;
				}
			}
		}
	}
}

void removeRoute(int r, vector<vector<int>>& con, vector<vector<int>>& p, vector<vector<int>>& c) {
	int s = routes[r][0];
	int e = routes[r][1];
	con[s][e] -= routes[r][2];
	for (int i = 0; i < p[s].size(); i++) {
		if (p[s][i] == e) {
			p[s].erase(p[s].begin() + i);
			c[s].erase(c[s].begin() + i);
			break;
		}
	}
	for (int i = 0; i < p[e].size(); i++) {
		if (p[e][i] == s) {
			p[e].erase(p[e].begin() + i);
			c[e].erase(c[e].begin() + i);
			break;
		}
	}
}

void addBack(int r, vector<vector<int>>& con, vector<vector<int>>& p, vector<vector<int>>& c) {
	int s = routes[r][0];
	int e = routes[r][1];
	int cost = routes[r][2];
	con[s][e] += routes[r][2];
	p[s].push_back(e);
	p[e].push_back(s);
	c[s].push_back(cost);
	c[e].push_back(cost);
}

int findFlow(vector<vector<int>>& usedCon, vector<vector<int>>& usedP, vector<vector<int>>& usedCosts) {
	int totalFlow = 0;
	int source = 0;
	int sink = N - 1;

	int flow[32];
	bool visited[32];
	int parents[32];
	int childIndex[32];
	int parentIndex[32];
	while (true) {
		memset(flow, -1, sizeof(flow));
		memset(visited, false, sizeof(visited));
		memset(parents, -1, sizeof(parents));
		memset(childIndex, -1, sizeof(childIndex));
		memset(parentIndex, -1, sizeof(parentIndex));
		flow[source] = INT_MAX;

		int index = -1;
		int neighborI = -1;
		while (true) {
			index = -1;
			int max = 0;
			for (int i = 0; i < N; i++) {
				if (flow[i] > max && !visited[i]) {
					max = flow[i];
					index = i;
				}
			}
			if (index == -1 || index == sink) {
				break;
			}
			visited[index] = true;
			for (int i = 0; i < usedP[index].size(); i++) {
				int next = usedP[index][i];
				int nextFlow = usedCosts[index][i];
				if (max < nextFlow || nextFlow == -1) {
					nextFlow = max;
				}

				if (flow[next] < nextFlow) {
					flow[next] = nextFlow;
					parents[next] = index;
					parentIndex[next] = i;
					int childI = -1;
					for (int j = 0; j < usedP[next].size(); j++) {
						if (usedP[next][j] == index) {
							childI = j;
							break;
						}
					}
					childIndex[index] = childI;
				}
			}
		}
		if (index == -1) {
			break;
		}

		int pathFlow = flow[sink];
		totalFlow += pathFlow;

		int current = sink;
		while (current != source) {
			int next = parents[current];
			int nextIn = parentIndex[current];
			usedCosts[next][nextIn] -= pathFlow;
			usedCosts[current][childIndex[next]] += pathFlow;
			current = next;
		}
	}
	return totalFlow;
}

void sortAns(vector<int>& r) {
	if (r.size() == 0) {
		return;
	}
	for (int i = 0; i < r.size() - 1; i++) {
		for (int j = i + 1; j < r.size(); j++) {
			if (routes[r[i]][3] > routes[r[j]][3]) {
				int tmp = r[i];
				r[i] = r[j];
				r[j] = tmp;
			}
		}
	}
}

bool alreadyRemoved(vector<int>& removed, int index) {
	for (int i = 0; i < removed.size(); i++) {
		if (removed[i] == index) {
			return true;
		}
	}
	return false;
}

int main() {
	ifstream fin("milk6.in");
	fin >> N >> M;
	connected.resize(N, vector<int>(N, 0));
	paths.resize(N);
	costs.resize(N);
	vector<vector<bool>> visitedPaths(N);
	for (int i = 0; i < M; i++) {
		vector<int> route;
		int S, E, C;
		fin >> S >> E >> C;
		S--;
		E--;
		connected[S][E] += C;
		route.push_back(S);
		route.push_back(E);
		route.push_back(C);
		route.push_back(i);
		paths[S].push_back(E);
		paths[E].push_back(S);
		costs[S].push_back(C);
		costs[E].push_back(0);
		visitedPaths[S].push_back(false);
		routes.push_back(route);
	}
	sortRoutes();

	vector<int> removed;
	vector<vector<int>> usedCon = connected;
	vector<vector<int>> usedP = paths;
	vector<vector<int>> usedCosts = costs;
	vector<vector<bool>> usedVP = visitedPaths;
	int flow = findFlow(usedCon, usedP, usedCosts);
	usedCon = connected;
	usedCosts = costs;
	int cost = 0;
	vector<bool> isRemoved(M, false);
	while (flow != 0) {
		for (int i = 0; i < M; i++) {
			if (isRemoved[i]) {
				continue;
			}
			isRemoved[i] = true;
			removed.push_back(i);
			removeRoute(i, usedCon, usedP, usedCosts);
			vector<vector<int>> con = usedCon;
			vector<vector<int>> c = usedCosts;
			int newFlow = findFlow(usedCon, usedP, usedCosts);
			if (flow - newFlow == routes[i][2]) {
				cost += routes[i][2];
				flow = newFlow;
				usedCon = con;
				usedCosts = c;
				break;
			}
			usedCon = con;
			usedCosts = c;
			addBack(i, usedCon, usedP, usedCosts);
			isRemoved[i] = false;
			removed.pop_back();
		}
	}

	ofstream fout("milk6.out");
	fout << cost << ' ' << removed.size() << '\n';
	sortAns(removed);
	for (int i = 0; i < removed.size(); i++) {
		fout << routes[removed[i]][3] + 1 << '\n';
	}
}