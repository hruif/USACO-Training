/*
ID: ruifanl1
TASK: race3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int N;
vector<bool> isUnavoidable, isSplitting, wentTo;
vector<int> unavoidables;
vector<vector<int>> paths;


void goNextNode(int node, vector<bool>& visited, vector<vector<int>>& usedPaths) {
	if (node == N) {
		visited[node] = true;
		for (int i = 0; i < unavoidables.size(); i++) {
			int toTest = unavoidables[i];
			if (!visited[toTest]) {
				isUnavoidable[toTest] = false;
				unavoidables.erase(unavoidables.begin() + i);
				i--;
			}
		}
		return;
	}

	visited[node] = true;
	for (int i = 0; i < usedPaths[node].size(); i++) {
		int next = usedPaths[node][i];
		if (visited[next]) {
			continue;
		}
		goNextNode(next, visited, usedPaths);
	}
	return;
}

void mapNext(int node, vector<bool>& visited) {
	if (node == N) {
		return;
	}
	visited[node] = true;
	for (int i = 0; i < paths[node].size(); i++) {
		int next = paths[node][i];
		if (visited[next]) {
			return;
		}
		mapNext(next, visited);
	}
	return;
}

bool checkSplitting(int node) {
	vector<bool> C1(N + 1, false);
	C1[node] = true;
	vector<bool> C2(N + 1, false);
	mapNext(0, C1);
	mapNext(node, C2);
	for (int i = 0; i < N + 1; i++) {
		if (C1[i] && C2[i]) {
			if (i != node) {
				return false;
			}
		}
	}
	return true;
}

void findUnavoidables() {
	for (int i = 1; i < N; i++) {
		vector<vector<int>> usedPaths = paths;
		vector<bool> visited(N + 1, false);
		for (int j = 0; j < usedPaths.size(); j++) {
			for (int k = 0; k < usedPaths[j].size(); k++) {
				if (usedPaths[j][k] == i) {
					usedPaths[j].erase(usedPaths[j].begin() + k);
				}
			}
		}

		goNextNode(0, visited, usedPaths);
		if (!visited[N]) {
			isUnavoidable[i] = true;
		}
	}
}

void solve() {
	/*
	vector<bool> visited(N + 1, false);
	wentTo.resize(N + 1, false);
	goNextNode(0, visited);
	*/

	findUnavoidables();

	for (int i = 0; i < N + 1; i++) {
		if (isUnavoidable[i] && checkSplitting(i)) {
			isSplitting[i] = true;
		}
	}
	return;
}

int main() {
	ifstream fin("race3.in");
	int tmp;
	fin >> tmp;
	vector<int> next;
	paths.push_back(next);
	while (tmp != -1) {
		if (tmp == -2) {
			N++;
			vector<int> next;
			paths.push_back(next);
			fin >> tmp;
			continue;
		}
		if (tmp != N) {
			paths[N].push_back(tmp);
		}
		fin >> tmp;
	}
	N--;
	isUnavoidable.resize(N + 1, true);
	isSplitting.resize(N + 1, false);
	isUnavoidable[0] = false;
	isUnavoidable[N] = false;
	for (int i = 1; i < N; i++) {
		unavoidables.push_back(i);
	}
	
	solve();

	ofstream fout("race3.out");
	vector<int> output;
	for (int i = 0; i < N + 1; i++) {
		if (isUnavoidable[i]) {
			output.push_back(i);
		}
	}

	int size = output.size();
	fout << size;
	if (size > 0) {
		fout << ' ';
		for (int i = 0; i < size; i++) {
			fout << output[i];
			if (i < size - 1) {
				fout << ' ';
			}
			else {
				fout << '\n';
			}
		}
		output.clear();
	}
	else {
		fout << '\n';
	}

	for (int i = 0; i < N + 1; i++) {
		if (isSplitting[i]) {
			output.push_back(i);
		}
	}

	size = output.size();
	fout << size;
	if (size > 0) {
		fout << ' ';
		for (int i = 0; i < size; i++) {
			fout << output[i];
			if (i < size - 1) {
				fout << ' ';
			}
			else {
				fout << '\n';
			}
		}
	}
	else {
		fout << '\n';
	}
}