/*
ID: ruifanl1
TASK: ditch
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> intersections, flowRates;

int findMin(int a, int b) {
	if (a == -1) {
		return b;
	}
	if (b == -1) {
		return a;
	}
	return a < b ? a : b;
}

int findAns() {
	int source = 0;
	int sink = M - 1;
	vector<vector<int>> capacity = flowRates;
	vector<int> flow(M);
	vector<int> prevnode(M);
	vector<bool> visited(M);

	int totalflow = 0;

	int c = 0;
	while (true) {

		int maxflow = 0;
		int maxloc = -1;

	// find path with highest capacity from
	// source to sink
	// uses a modified djikstra's algorithm
		for (int i = 0; i < M; i++) {
			prevnode[i] = -1;
			flow[i] = 0;
			visited[i] = false;
		}
		flow[source] = INT_MAX;

		while (true) {
			maxflow = 0;
			maxloc = -1;
			c++;
			if (c == 795) {
				int a = 5;
			}
			// find the unvisited node with
			// the ghiest capacity to it
			for (int i = 0; i < M; i++) {
				if (flow[i] > maxflow && !visited[i]) {
					maxflow = flow[i];
					maxloc = i;
				}
			}
			if (maxloc == -1) {
				break;
			}
			if (maxloc == sink) {
				break;
			}
			visited[maxloc] = true;
			// updates its neighbors
			for (int j = 0; j < intersections[maxloc].size(); j++) {
				int i = intersections[maxloc][j];

				if (flow[i] < min(maxflow, 
						capacity[maxloc][i])) {
					prevnode[i] = maxloc;
					flow[i] = min(maxflow,
							capacity[maxloc][i]);
				}
			}
		}

		if (maxloc == -1) {	// no path
			break;
		}
		
		int pathcapacity = flow[sink];
		totalflow = totalflow + pathcapacity;

	// add that flow to the network,
	// update capacity appropriately
		int curnode = sink;
			// for each arc, prevnode(curnode),
			// curnode on path:
		while (curnode != source) {
			int nextnode = prevnode[curnode];
			capacity[nextnode][curnode] =
				capacity[nextnode][curnode] -
									pathcapacity;
			capacity[curnode][nextnode] =
				capacity[curnode][nextnode] +
									pathcapacity;
			curnode = nextnode;
		}
	}

	return totalflow;
}

int main() {
	ifstream fin("ditch.in");
	fin >> N >> M;
	flowRates.resize(M, vector<int>(M, 0));
	intersections.resize(M + 1);
	for (int i = 0; i < N; i++) {
		int S, E, C;
		fin >> S >> E >> C;
		S--;
		E--;
		intersections[S].push_back(E);
		intersections[E].push_back(S);
		flowRates[S][E] += C;
	}

	int ans = findAns();

	ofstream fout("ditch.out");
	fout << ans << '\n';
}