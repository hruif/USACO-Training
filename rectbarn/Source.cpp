/*
ID: ruifanl1
TASK: rectbarn
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string.h>
#include <algorithm>
#include <climits>

using namespace std;

int R, C, P, ans;
vector<vector<vector<int>>> found;
vector<vector<int>> ruined;

void sortRuined() {
	for (int i = 0; i < R; i++) {
		int len = ruined[i].size();
		for (int j = 0; j < len - 1; j++) {
			for (int k = j + 1; k < len; k++) {
				if (ruined[i][j] > ruined[i][k]) {
					int t = ruined[i][j];
					ruined[i][j] = ruined[i][k];
					ruined[i][k] = t;
				}
			}
		}
	}
}

void findRect(int x, int y) {
	int height = found[0][y][0] + 1;
	int maxLeft = 0;
	int maxRight = C - 1;
	for (int i = 0; i < ruined[x].size(); i++) {
		int square = ruined[x][i];
		if (square < y) {
			maxLeft = square + 1;
		}
		if (square == y) {
			found[1][y][0] = 0;
			found[1][y][1] = y;
			found[1][y][2] = y;
			return;
		}
		if (square > y) {
			maxRight = square - 1;
			break;
		}
	}

	int left = y;
	int right = y;
	for (int i = left - 1; i >= maxLeft; i--) {
		if (found[1][i][0] >= height) {
			i = max(found[1][i][1], maxLeft);
			if (found[1][i][2] > right) {
				right = min(found[1][i][2], maxRight);
			}
			left = i;
		}
		else {
			break;
		}
	}
	for (int i = right + 1; i <= maxRight; i++) {
		if (found[0][i][0] + 1 >= height) {
			i = min(found[0][i][2], maxRight);
			right = i;
		}
		else {
			right = i - 1;
			break;
		}
	}
	found[1][y][0] = height;
	found[1][y][1] = left;
	found[1][y][2] = right;
	int w = right - left + 1;
	int area = w * height;
	if (area > ans) {
		ans = area;
	}
}

int main() {
	ifstream fin("rectbarn.in");
	fin >> R >> C >> P;
	ruined.resize(R);
	for (int i = 0; i < P; i++) { // input
		pair<int, int> t;
		fin >> t.first >> t.second;
		ruined[t.first - 1].push_back(t.second - 1); // all ruined squares for every row
	}
	found.resize(2, vector<vector<int>>(C, vector<int>(3)));
	for (int i = 0; i < C; i++) { // set found[0]
		found[0][i][0] = 0;
		found[0][i][1] = i;
		found[0][i][2] = i;
	}
	sortRuined(); // sort ruined squares

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			findRect(i, j); // find 
		}
		found[0] = found[1];
	}

	ofstream fout("rectbarn.out");
	fout << ans << '\n';
}