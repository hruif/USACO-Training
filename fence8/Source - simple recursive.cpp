/*
ID: ruifanl1
TASK: fence8
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool found = false;
int N, R, total;
vector<int> boards;
vector<int> rails;

void sortRails() {
	for (int i = 0; i < rails.size() - 1; i++) {
		for (int j = i + 1; j < rails.size(); j++) {
			if (rails[i] > rails[j]) {
				int t = rails[i];
				rails[i] = rails[j];
				rails[j] = t;
			}
		}
	}
}

int cutRail(int r, int leftover) {
	if (r == R) {
		return 0;
	}
	if (leftover < rails[r]) {
		found = true;
		return 0;
	}
	int best = 0;
	for (int i = 0; i < boards.size(); i++) {
		boards[i] -= rails[r];
		leftover -= rails[r];
		if (boards[i] >= 0) {
			int t = cutRail(r + 1, leftover) + 1;
			if (found) {
				return t;
			}
			if (t > best) {
				best = t;
			}
		}
		leftover += rails[r];
		boards[i] += rails[r];
	}
	return best;
}

void splitBoard(int board, vector<bool>& cut) {

}

int main() {
	ifstream fin("fence8.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int t;
		fin >> t;
		total += t;
		boards.push_back(t);
	}
	fin >> R;
	for (int i = 0; i < R; i++) {
		int t;
		fin >> t;
		rails.push_back(t);
	}

	vector<bool> cut(R, false);
	
	sortRails();
	int ans = cutRail(0, total);

	ofstream fout("fence8.out");
	fout << ans << '\n';
}