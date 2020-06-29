/*
ID: ruifanl1
TASK: range
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N;
vector<int> ans;
vector<vector<int>> largestSquares;
vector<vector<bool>> ravaged;

int minOf(int a, int b) {
	return a < b ? a : b;
}

int findLargestSquare(int x, int y) {
	int w = -1, l = 0, highest = 0;
	for (int j = y; j < N; j++) {
		int rowWidth = 0;
		for (int i = x; i < N; i++) {
			if (ravaged[j][i]) {
				break;
			}
			int val = largestSquares[i][j];
			if (val != -1) {
				rowWidth += val;
				i += val - 1;
			}
			else {
				rowWidth++;
			}
		}
		l++;
		if (rowWidth < w || w == -1) {
			w = rowWidth;
		}
		int min = minOf(l, w);
		if (min > highest) {
			highest = min;
		}
		if (w < 2) {
			break;
		}
		if (l >= w) {
			largestSquares[x][y] = highest;
			return highest;
		}
	}
	largestSquares[x][y] = highest;
	return highest;
}

int main() {
	ifstream fin("range.in");
	fin >> N;
	ans.resize(N, 0);
	for (int i = 0; i < N; i++) {
		vector<bool> tmpField;
		for (int j = 0; j < N; j++) {
			char tmp;
			fin >> tmp;
			if (tmp == '0') {
				tmpField.push_back(true);
			}
			else {
				tmpField.push_back(false);
			}
		}
		ravaged.push_back(tmpField);
	}
	largestSquares.resize(N, vector<int>(N, -1));

	for (int y = N - 1; y >= 0; y--) {
		for (int x = N - 1; x >= 0; x--) {
			int len = findLargestSquare(x, y);
			for (int i = len; i >= 2; i--) {
				ans[i - 1]++;
			}
		}
	}

	ofstream fout("range.out");
	for (int i = 0; i < ans.size(); i++) {
		if (ans[i] > 0) {
			fout << i + 1 << ' ' << ans[i] << '\n';
		}
	}
}