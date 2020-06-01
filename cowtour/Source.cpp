/*
ID: ruifanl1
TASK: cowtour
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int N;
vector<double> diamsThroughPasture;
vector<double> diams;
vector<vector<int>> pastures, connectedPastures;
vector<vector<bool>> connectFlags;

double distTo(int a, int b) {
	double distX = pastures[a][0] - pastures[b][0];
	double distY = pastures[a][1] - pastures[b][1];
	double returnVal = sqrt(distX * distX + distY * distY);
	return returnVal;
}

void findPaths(int start) {
	vector<bool> visited(N);
	vector<bool> discovered(N);
	vector<double> distances(N, -1);
	visited[start] = true;
	discovered[start] = true;
	distances[start] = 0;

	for (int i = 0; i < connectedPastures[start].size(); i++) {
		int p = connectedPastures[start][i];
		distances[p] = distTo(start, p);
		discovered[p] = true;
	}

	for (int i = 1; i < N; i++) {
		double shortest = -1;
		int p = start;
		for (int j = 0; j < N; j++) {
			if (!visited[j] && discovered[j]) {
				double dist = distances[j];
				if (dist < shortest || shortest < 0) {
					shortest = dist;
					p = j;
				}
			}
		}
		if (p == start) {
			break;
		}
		visited[p] = true;
		for (int j = 0; j < connectedPastures[p].size(); j++) {
			int nextP = connectedPastures[p][j];
			if (visited[nextP]) {
				continue;
			}
			double dist = distTo(p, nextP) + distances[p];
			if (dist < distances[nextP] || distances[nextP] < 0) {
				distances[nextP] = dist;
			}
			discovered[nextP] = true;
		}
	}

	double longestThrough = 0;
	double longest = 0;
	for (int i = 0; i < N; i++) {
		double dist = distances[i];
		if (dist >= 0) {
			connectFlags[start][i] = true;
			if (dist > longestThrough) {
				longestThrough = dist;
			}
		}
	}
	diamsThroughPasture[start] = longestThrough;
}

double connect(int p1, int p2) {
	double newDiam = diamsThroughPasture[p1] + distTo(p1, p2) + diamsThroughPasture[p2];
	newDiam = max(newDiam, diams[p1]);
	newDiam = max(newDiam, diams[p2]);
	return newDiam;
}

int main() {
	ifstream fin("cowtour.in");
	fin >> N;
	diamsThroughPasture.resize(N, -1);
	diams.resize(N, -1);
	for (int i = 0; i < N; i++) {
		vector<int> pasture;
		int x, y;
		fin >> x >> y;
		pasture.push_back(x);
		pasture.push_back(y);
		pastures.push_back(pasture);
	}

	for (int i = 0; i < N; i++) {
		vector<bool> flags;
		vector<int> tmpConnectedPastures;
		for (int j = 0; j < N; j++) {
			char tmp;
			fin >> tmp;
			tmp -= '0';
			if (tmp == 1) {
				tmpConnectedPastures.push_back(j);
			}
			flags.push_back(tmp);
		}
		connectFlags.push_back(flags);
		connectedPastures.push_back(tmpConnectedPastures);
	}

	for (int i = 0; i < N; i++) {
		findPaths(i);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!connectFlags[i][j]) {
				continue;
			}
			if (diams[i] < diamsThroughPasture[j]) {
				diams[i] = diamsThroughPasture[j];
			}
		}
	}
	double ans = -1;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (!connectFlags[i][j] && i != j) {
				double diam = connect(i, j);
				if (diam < ans || ans < 0) {
					ans = diam;
				}
			}
		}
	}

	FILE* fout = fopen("cowtour.out", "w");
	fprintf(fout, "%.6f\n", ans);
	fclose(fout);
}