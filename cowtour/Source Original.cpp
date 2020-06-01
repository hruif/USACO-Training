/*
ID: ruifanl1
TASK: cowtour
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
// descriptions below code

using namespace std;

int N;
vector<double> longPath;
vector<vector<bool>> paths;
vector<vector<double>> pastures, allDistances;
vector<vector<int>> connected;
// globals

double distTo(int p1, int p2) {
// finds distance between two points
	double a = pastures[p1][0] - pastures[p2][0];
	double b = pastures[p1][1] - pastures[p2][1];
	return sqrt(a * a + b * b);
}

double nextPasture(vector<bool>& visited, vector<double>& p, int index) {
// finds next pasture and outputs shortest distance between it and index
	double shortest = -1;
	int pasture = index;
	for (int i = 0; i < N; i++) {
		double a = p[i];
		if (a > 0 && !visited[i]) {
			if (shortest == -1 || a < shortest) {
				shortest = a;
				pasture = i;
			}
		}
	}
	// finds shortest path (dijkstra)
	if (pasture == index) {
		return -1;
	}
	visited[pasture] = true;
	for (int i = 0; i < connected[pasture].size(); i++) {
		int next = connected[pasture][i];
		double dist = distTo(next, pasture) + p[pasture];
		double tmp = p[next];
		if (dist < tmp || tmp  == -1) {
			p[next] = dist;
		}
	}
	// changes values if shorter path (dijkstra)
	return shortest;
}

double findPath(vector<double>& p, int index) {
	vector<bool> visited(N, false);
	p[index] = 0;
	visited[index] = true;
	for (int i = 0; i < connected[index].size(); i++) {
		int pasture = connected[index][i];
		p[pasture] = distTo(pasture, index);
	}
	// sets all nodes connected to index
	double longest = -1;
	while (true) {
		double tmp = nextPasture(visited, p, index);
		// checks each number
		if (tmp == -1) {
			return longest;
		}
		if (tmp > longest) {
			longest = tmp;
		}
	}
	// finds diameter
}

double connect(int p1, int p2) {
	double val = distTo(p1, p2) + longPath[p1] + longPath[p2];
	if (longPath[p1] == -1) {
		val -= longPath[p1];
	}
	if (longPath[p2] == -1) {
		val -= longPath[p2];
	}
// return diameter after connecting p1 and p2
	/*
	vector<double> paths(N, -1);
	paths[p1] = 0;
	for (int i = 0; i < connected[p1].size(); i++) {
		if (connected[p1][i] == p2) {
			return -1;
		}
	}
	/*
	// check they're not already connected
	connected[p1].push_back(p2);
	connected[p2].push_back(p1);
	// connect
	double val = findPath(paths, p1);l,
	connected[p1].pop_back();
	connected[p2].pop_back();
	// deconnect
	return val;
	/

	double dist = distTo(p1, p2);
	double val = 0;
	int size = allDistances[p1].size();

	for (int k = 0; k < connected[p1].size(); k++) {
		int j = connected[p1][k];
		int p = -1;
		double tmpDist = dist;
		if (allDistances[p1][j] >= 0) {
			p = p2;
			tmpDist += allDistances[p1][j];
		}
		if (p == -1) {
			p = p1;
			tmpDist += allDistances[p2][j];
		}
		for (int i = 0; i < N; i++) {
			double tmp;
			double dist1 = allDistances[j][i];
			double dist2 = allDistances[p][i];
			if (dist1 == -1) {
				if (dist2 == -1) {
					continue;
				}
				tmp = dist2 + tmpDist;
			}
			else if (dist2 == -1) {
				tmp = dist1;
			}
			else {
				tmp = dist1 < dist2 + tmpDist ? dist1 : dist2 + tmpDist;
			}
			if (tmp > val) {
				val = tmp;
			}
		}
	}
	*/
	return val;
}

int main() {
	ifstream fin("cowtour.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		vector<double> pasture;
		vector<bool> path(N, false);
		paths.push_back(path);
		for (int j = 0; j < 2; j++) {
			double tmp;
			fin >> tmp;
			pasture.push_back(tmp);
		}
		pastures.push_back(pasture);
	}
	longPath.resize(N, 0);
	// sets pastures
	for (int i = 0; i < N; i++) {
		vector<int> connect;
		for (int j = 0; j < N; j++) {
			char digit;
			fin >> digit;
			digit -= '0';
			if (digit == 1) {
				connect.push_back(j);
				paths[i][j] = true;
			}
		}
		connected.push_back(connect);
	}
	// sets paths
	for (int i = 0; i < N; i++) {
		vector<double> tmp(N, -1);
		allDistances.push_back(tmp);
	}
	double ans = 0;
	// sets allDistance array (all distances from each pasture to every other)

	for (int i = 0; i < N; i++) {
		findPath(allDistances[i], i);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (allDistances[i][j] >= 0) {
				paths[i][j] = true;
			}
		}
	}
	connected.clear();
	for (int i = 0; i < N; i++) {
		vector<int> connections;
		for (int j = 0; j < N; j++) {
			if (allDistances[i][j] >= 0) {
				connections.push_back(j);
			}
		}
		connected.push_back(connections);
	}
	// finds and sets all paths and connections
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			double tmp = allDistances[i][j];
			if (tmp > longPath[i]) {
				longPath[i] = tmp;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (paths[i][j]) {
				continue;
			}
			double dist = distTo(i, j);
			if (dist != allDistances[i][j]) {
				double diam = connect(i, j);
				// connects i and j
				if (diam < ans || ans == 0) {
					if (diam > 0) {
						ans = diam;
					}
				}
				// finds diam
			}
		}
	}
	FILE* fout = fopen("cowtour.out", "w");
	fprintf(fout, "%.6f\n", ans);
	fclose(fout);
}