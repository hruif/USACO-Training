/*
ID; ruifanl1
TASK: comehome
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int P;
vector<int> cows;
vector<vector<vector<int>>> paths;

int findHome(int cow) {
	vector<int> distances(52, -1);
	vector<bool> visited(52);
	vector<bool> discovered(52);
	visited[cow] = true;

	for (int i = 0; i < paths[cow].size(); i++) {
		if (paths[cow][i][1] < distances[paths[cow][i][0]] || distances[paths[cow][i][0]] < 0) {
			discovered[paths[cow][i][0]] = true;
			distances[paths[cow][i][0]] = paths[cow][i][1];
		}
	}

	while (true) {
		int p, shortest = -1;
		for (int i = 0; i < 52; i++) {
			if (!visited[i] && discovered[i]) {
				int dist = distances[i];
				if (dist < shortest || shortest < 0) {
					shortest = dist;
					p = i;
				}
			}
		}
		if (p == 51) {
			return distances[51];
		}
		visited[p] = true;

		for (int i = 0; i < paths[p].size(); i++) {
			int nextP = paths[p][i][0];
			int dist = paths[p][i][1] + distances[p];
			if (dist < distances[nextP] || distances[nextP] < 0) {
				discovered[nextP] = true;
				distances[nextP] = dist;
			}
		}
	}
}

int main() {
	ifstream fin("comehome.in");
	ofstream fout("comehome.out");
	for (int i = 0; i < 51; i++) {
		vector<vector<int>> tmp;
		paths.push_back(tmp);
	}
	fin >> P;
	vector<vector<int>> allDistances;
	for (int i = 0; i < 52; i++) {
		vector<int> tmp(52, -1);
		allDistances.push_back(tmp);
	}
	for (int i = 0; i < P; i++) {
		int dist;
		char p1, p2;
		fin >> p1 >> p2 >> dist;
		if (isupper(p1)) {
			p1 -= 'A';
			p1 += 26;
		}
		else {
			p1 -= 'a';
		}
		if (isupper(p2)) {
			p2 -= 'A';
			p2 += 26;
		}
		else {
			p2 -= 'a';
		}

		if (dist < allDistances[p1][p2] || allDistances[p1][p2] < 0) {
			allDistances[p1][p2] = allDistances[p2][p1] = dist;
		}
	}
	for (int i = 0; i < 51; i++) {
		bool cow = false;
		for (int j = 0; j < 52; j++) {
			int dist = allDistances[i][j];
			if (dist >= 0) {
				cow = true;
				vector<int> tmpPath;
				tmpPath.push_back(j);
				tmpPath.push_back(dist);
				paths[i].push_back(tmpPath);
			}
		}
		if (cow && i >= 26) {
			cows.push_back(i);
		}
	}
	char bruh = 'S' - 'A' + 26;
	int ans = -1;
	char cow;
	for (int i = 0; i < cows.size(); i++) {
		int tmp = cows[i];
		int path = findHome(tmp);
		if (path < ans || ans < 0) {
			ans = path;
			cow = tmp;
		}
	}
	if (cow >= 26) {
		cow -= 26;
		cow += 'A';
	}
	else {
		cow += 'a';
	}
	fout << cow << ' ' << ans << '\n';
}