/*
ID: ruifanl1
TASK: snail
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

int N, B;
vector<vector<bool>> hasBarrier;
vector<pair<int, int>> barriers;

bool moveInDir(pair<int, int>& next, int direction){
	if (direction == 0) {
		next.second--;
	}
	if (direction == 1) {
		next.first++;
	}
	if (direction == 2) {
		next.second++;
	}
	if (direction == 3) {
		next.first--;
	}
	if (next.first < 0 || next.second < 0) {
		return false;
	}
	if (next.first >= N || next.second >= N) {
		return false;
	}
	if (hasBarrier[next.first][next.second]) {
		return false;
	}
	return true;
}

int findMaxDist(int x, int y, int direction, vector<vector<bool>>& visited) {
	int dist = 0;
	pair<int, int> current(x, y);
	pair<int, int> next = current;
	if (!moveInDir(next, direction) || visited[next.first][next.second]) {
		return false;
	}
	int max = 0;
	vector<pair<int, int>> travelled; // nodes current function call has visited
	while (!visited[next.first][next.second]) {
		dist++;
		current = next;
		visited[next.first][next.second] = true;
		travelled.push_back(next);
		if (!moveInDir(next, direction)) {
			if (direction == 0) {
				max = findMaxDist(current.first, current.second, 3, visited);
			}
			else {
				max = findMaxDist(current.first, current.second, direction - 1, visited);
			}
			int tmp;
			if (direction == 3) {
				tmp = findMaxDist(current.first, current.second, 0, visited);
			}
			else {
				tmp = findMaxDist(current.first, current.second, direction + 1, visited);
			}
			if (tmp > max) {
				max = tmp;
			}
			break;
		}
	}
	for (int i = 0; i < travelled.size(); i++) {
		visited[travelled[i].first][travelled[i].second] = false;
	}
	return max + dist;
}

int main() {
	ifstream fin("snail.in");
	fin >> N >> B;
	hasBarrier.resize(N, vector<bool>(N, false));
	for (int i = 0; i < B; i++) {
		char letter;
		int num;
		fin >> letter >> num;
		hasBarrier[letter - 'A'][num - 1] = true;
		pair<int, int> tmp(letter - 'A', num - 1);
		barriers.push_back(tmp);
	}

	int ans = 1;

	vector<vector<bool>> visited(N, vector<bool>(N, false));
	visited[0][0] = true;
	int max = findMaxDist(0, 0, 1, visited);
	int tmp = findMaxDist(0, 0, 2, visited);
	if (tmp > max) {
		max = tmp;
	}
	ans += max;

	ofstream fout("snail.out");
	fout << ans << '\n';
}