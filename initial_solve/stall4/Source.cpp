/*
ID: ruifanl1
TASK: stall4
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> connected; // convert for network flow algorithm
vector<vector<bool>> isWilling;

int findAns() {
	int source = 0;
	int sink = M + N + 1;
	int total = 0;
	vector<vector<bool>> usedWilling = isWilling;

	while (true) {
		vector<bool> visited(N + M + 2, false);
		vector<int> parent(N + M + 2, -1);
		vector<bool> canChoose(N + M + 2, false);
		canChoose[0] = true;

		int index = -1;
		while (true) {
			int chosen = -1;
			for (int i = 0; i < N + M + 2; i++) {
				if (canChoose[i] && !visited[i]) {
					chosen = i;
					break;
				}
			}
			index = chosen;
			if (chosen == -1 || chosen == sink) {
				break;
			}
			visited[chosen] = true;
			for (int i = 0; i < connected[chosen].size(); i++) {
				int next = connected[chosen][i];
				if (usedWilling[chosen][next] && parent[next] == -1) {
					parent[next] = chosen;
					canChoose[next] = true;
				}
			}
		}

		if (index == -1) {
			break;
		}

		total++;

		int current = sink;
		while (current != source) {
			int next = parent[current];
			usedWilling[next][current] = !usedWilling[next][current];
			usedWilling[current][next] = !usedWilling[current][next];
			current = next;
		}
	}
	return total;
}

int main() {
	ifstream fin("stall4.in");
	fin >> N >> M;
	connected.resize(N + M + 2);
	isWilling.resize(N + M + 2, vector<bool>(N + M + 2, false));
	for (int i = 0; i < N; i++) {
		connected[0].push_back(i + 1);
		isWilling[0][i + 1] = true;
		int S;
		fin >> S;
		for (int j = 0; j < S; j++) {
			int tmp;
			fin >> tmp;
			connected[i + 1].push_back(tmp + N);
			connected[tmp + N].push_back(i + 1);
			isWilling[i + 1][tmp + N] = true;
		}
	}
	for (int i = N + 1; i < N + M + 1; i++) {
		isWilling[i][N + M + 1] = true;
		connected[i].push_back(N + M + 1);
		connected[N + M + 1].push_back(i);
	}

	int ans = 0;
	if (N != 0 && M != 0) {
		ans = findAns();
	}

	ofstream fout("stall4.out");
	fout << ans << '\n';
}