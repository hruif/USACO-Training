/*
ID: ruifanl1
TASK: hamming
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, B, D, largestNum;
vector<vector<int>> distances;
vector<bool> hammingFlags;
vector<int> solution;

int powerOf(int val, int power) {
	int result = val;
	for (int i = 1; i < power; i++) {
		result *= val;
	}
	return result;
}

int computeHammingDistance(int a, int b) {
	int distance = 0;
	int mask = 1;
	for (int i = 0; i < B; i++) {
		if ((mask & a) != (mask & b)) {
			distance++;
		}
		mask <<= 1;
	}
	return distance;
}

void computeDistances() {
	distances.resize(largestNum);
	for (int i = 0; i < largestNum; i++) {
		distances[i].resize(largestNum);
	}
	for (int i = 0; i < largestNum; i++) {
		for (int j = i; j < largestNum; j++) {
			distances[i][j] = distances[j][i] = computeHammingDistance(i, j);
		}
	}
}

void dfs() {
	for (int i = 0; i < largestNum; i++) {
		if (hammingFlags[i]) {
			continue;
		}
		solution.push_back(i);
		if (solution.size() == N) {
			return;
		}
		vector<int> newFlags;
		for (int j = 0; j < largestNum; j++) {
			if (distances[i][j] < D) {
				if (!hammingFlags[j]) {
					newFlags.push_back(j);
				}
				hammingFlags[j] = true;
			}
		}
		dfs();
		if (solution.size() == N) {
			return;
		}
		for (int j = 0; j < newFlags.size(); j++) {
			hammingFlags[newFlags[j]] == false;
		}
		solution.pop_back();
	}
}

int main() {
	ifstream fin("hamming.in");
	fin >> N >> B >> D;
	largestNum = powerOf(2, B);
	for (int i = 0; i < largestNum; i++) {
		hammingFlags.push_back(false);
	}
	computeDistances();

	dfs();
	ofstream fout("hamming.out");
	for (int i = 0; i < N; i++) {
		if (i > 0 && i % 10 == 0) {
			fout << '\n';
		}
		if (i % 10 != 0) {
			fout << ' ';
		}
		fout << solution[i];
	}
	fout << '\n';
}