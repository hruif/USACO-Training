/*
ID: ruifanl1
TASK: telecow
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

int N, M, c1, c2;
vector<vector<int>> E;

void removeEdge(vector<vector<int>>& edges, int edge) {
	edges[edge * 2][edge * 2 + 1] = -1;
}

void addEdge(vector<vector<int>>& edges, int edge) {
	edges[edge * 2][edge * 2 + 1] = E[edge * 2][edge * 2 + 1];
}

int findFlow(vector<vector<int>>& edges) {
	int source = c1 * 2 + 1;
	int sink = c2 * 2;
	int totalFlow = 0;
	int len = edges.size();
	while (true) {
		vector<int> flow(len, -1);
		vector<int> parents(len, -1);
		vector<bool> visited(len, false);
		flow[source] = INT_MAX;

		int index = -1;
		while (true) {
			int best = 0;
			index = -1;
			for (int i = 0; i < len; i++) {
				if (flow[i] > best && !visited[i]) {
					best = flow[i];
					index = i;
				}
			}
			if (index == -1 || index == sink) {
				break;
			}
			visited[index] = true;
			for (int i = 0; i < len; i++) {
				if (edges[index][i] == 0) {
					continue;
				}
				int min = edges[index][i] < best ? edges[index][i] : best;
				if (min > flow[i]) {
					flow[i] = min;
					parents[i] = index;
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
			edges[next][current] -= pathFlow;
			edges[current][next] += pathFlow;
			current = next;
		}
	}
	return totalFlow;
}

int main() {
	ifstream fin("telecow.in");
	fin >> N >> M >> c1 >> c2;
	c1--;
	c2--;
	E.resize(N * 2, vector<int>(N * 2, 0));
	for (int i = 0; i < N; i++) {
		E[i * 2][i * 2 + 1] = 1;
	}
	for (int i = 0; i < M; i++) {
		int id1, id2;
		fin >> id1 >> id2;
		id1--;
		id2--;
		E[id1 * 2 + 1][id2 * 2] = 1000;
		E[id2 * 2 + 1][id1 * 2] = 1000;
	}

	vector<vector<int>> edges = E;
	int totalFlow = findFlow(edges);
	edges = E;
	vector<bool> isRemoved(N, false);
	int last = 0;
	int a = 0;
	while (totalFlow != 0) {
		a++;
		for (int i = last + 1; i < N; i++) {
			removeEdge(edges, i);
			vector<vector<int>> tmpEdge = edges;
			int newFlow = findFlow(edges);
			edges = tmpEdge;
			if (newFlow == totalFlow - 1) {
				isRemoved[i] = true;
				last = i;
				totalFlow = newFlow;
				break;
			}
			addEdge(edges, i);
		}
	}

	ofstream fout("telecow.out");
	vector<int> output;
	for (int i = 0; i < N; i++) {
		if (isRemoved[i]) {
			output.push_back(i + 1);
		}
	}
	fout << output.size();
	for (int i = 0; i < output.size(); i++) {
		if (i == 0) {
			fout << '\n';
		}
		else {
			fout << ' ';
		}
		fout << output[i];
	}
	fout << '\n';
}