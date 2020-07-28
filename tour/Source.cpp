/*
ID: ruifanl1
TASK: tour
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int N, V;
bool canReach = false;
vector<vector<bool>> E; // adjacency matrix for edges
vector<vector<int>> found; // cache to store found answers

int findM(int a, int b) {
	if (a == 0 && b == 0) {
		return 1;
	}
	if (a > b) {
		int t = a;
		a = b;
		b = t;
	}
	if (found[a][b] != -2) {
		return found[a][b];
	}
	
	int best = -1;
	for (int u = b - 1; u >= 0; u--) {
		if (a != 0) {
			if (a == u) {
				continue;
			}
		}
		if (!E[b][u]) {
			continue;
		}

		int score = findM(a, u);
		if (score < 0) {
			continue;
		}
		score++;
		if (score > best) {
			best = score;
		}
	}

	if (best == -1) {
		found[a][b] = best;
		found[b][a] = best;
		return best;
	}

	if (a == b) {
		best--;
	}
	found[a][b] = best;
	found[b][a] = best;
	return best;
}

int main() {
	ifstream fin("tour.in");
	fin >> N >> V;
	E.resize(N, vector<bool>(N, false));
	found.resize(N, vector<int>(N, -2));
	vector<string> cities;
	for (int i = 0; i < N; i++) {
		string city;
		fin >> city;
		cities.push_back(city);
	}
	for (int i = 0; i < V; i++) {
		string c1, c2;
		fin >> c1 >> c2;
		int c1Index;
		int c2Index;
		for (int j = 0; j < N; j++) {
			if (cities[j] == c1) {
				c1Index = j;
			}
			if (cities[j] == c2) {
				c2Index = j;
			}
		}
		E[c1Index][c2Index] = true;
		E[c2Index][c1Index] = true;
	}
	
	found[0][0] = 1;
	int M = findM(N - 1, N - 1);
	if (M == -1) {
		M = 1;
	}

	ofstream fout("tour.out");
	fout << M  << '\n';
}