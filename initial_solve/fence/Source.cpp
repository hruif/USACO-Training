/*
ID: ruifanl1
TASK: fence
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int F;
vector<vector<int>> connected(500);

void deleteEdge(int a, int aIndex, int b) {
	int bIndex;
	for (int i = 0; i < connected[b].size(); i++) {
		if (connected[b][i] == a) {
			bIndex = i;
			break;
		}
	}

	connected[a].erase(connected[a].begin() + aIndex);
	connected[b].erase(connected[b].begin() + bIndex);
}

int findNext(int a) {
	int next = -1;
	int nextIndex = -1;
	for (int i = 0; i < connected[a].size(); i++) {
		if (connected[a][i] < next || next == -1) {
			next = connected[a][i];
			nextIndex = i;
		}
	}
	return nextIndex;
}

void findPath(int intersect, vector<int>& ans) {
	if (connected[intersect].empty()) {
		ans.push_back(intersect);
	}
	else {
		while (!connected[intersect].empty()) {
			int nextIndex = findNext(intersect);
			int next = connected[intersect][nextIndex];
			deleteEdge(intersect, nextIndex, next);
			findPath(next, ans);
		}
		ans.push_back(intersect);
	}
}

int main() {
	ifstream fin("fence.in");
	fin >> F;
	int smallest = -1;
	for (int i = 0; i < F; i++) {
		int intersection1, intersection2;
		fin >> intersection1 >> intersection2;
		intersection1--;
		intersection2--;
		if (smallest > intersection1 || smallest == -1) {
			smallest = intersection1;
		}
		if (smallest > intersection2) {
			smallest = intersection2;
		}
		connected[intersection1].push_back(intersection2);
		connected[intersection2].push_back(intersection1);
	}

	int start = -1;
	for (int i = 0; i < connected.size(); i++) {
		if (connected[i].size() % 2 == 1) {
			if (i < start || start == -1) {
				start = i;
			}
		}
	}
	if (start == -1) {
		start = smallest;
	}

	vector<int> ans;
	findPath(start, ans);

	ofstream fout("fence.out");
	for (int i = ans.size() - 1; i >= 0; i--) {
		fout << ans[i] + 1 << '\n';
	}
}