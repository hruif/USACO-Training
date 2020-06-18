/*
ID: ruifanl1
TASK: agrinet
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> distances;

void changePaths(vector<int>& dists, vector<bool>& visited, int next) {
	for (int i = 0; i < N; i++) {
		if (!visited[i] && (distances[next][i] < dists[i] || dists[i] == -1)) {
			dists[i] = distances[next][i];
		}
	}
}

int findShortest(vector<int>& dists, vector<bool>& visited) {
	int next = 0, shortest = -1;
	for (int i = 0; i < N; i++) {
		if (dists[i] < shortest || shortest == -1) {
			if (!visited[i]) {
				next = i;
				shortest = dists[i];
			}
		}
	}
	return next;
}

int solve() {
	vector<int> dists(N, -1);
	vector<bool> visited(N, false);
	int next = 0, ans = 0;
	for (int i = 0; i < N; i++) {
		next = findShortest(dists, visited);
		visited[next] = true;
		changePaths(dists, visited, next);
	}
	for (int i = 0; i < N; i++) {
		ans += dists[i];
	}
	return ans + 1;
}

int main() {
	ifstream fin("agrinet.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		vector<int> farm;
		for (int j = 0; j < N; j++) {
			int tmp;
			fin >> tmp;
			farm.push_back(tmp);
		}
		distances.push_back(farm);
	}
	int ans = solve();
	ofstream fout("agrinet.out");
	fout << ans << '\n';
}