/*
ID: ruifanl1
TASK: bigbrn
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int N, T;
int ans;
vector<pair<int, int>> ts;
vector<vector<int>> maxSquares;
vector<vector<bool>> parcels;

void checkAns(int val) {
	if (val > ans) {
		ans = val;
	}
}

int findMaxSquareFrom(int x, int y) {
	if (maxSquares[x][y] != -1) {
		return maxSquares[x][y];
	}
	int a = -1;
	int b = -1;
	int c = -1;
	if (x > 0 && y > 0) {
		a = findMaxSquareFrom(x - 1, y - 1) + 1;
		b = findMaxSquareFrom(x - 1, y) + 1;
		c = findMaxSquareFrom(x, y - 1) + 1;
	}
	else {
		if (parcels[x][y]) {
			maxSquares[x][y] = 0;
			return 0;
		}
		else {
			maxSquares[x][y] = 1;
			checkAns(1);
			return 1;
		}
	}
	int max = 0;
	if (!parcels[x][y]) {
		int min = -1;
		if (a != -1) {
			min = a;
		}
		if (b < min || min == -1) {
			min = b;
		}
		if (c < min || min == -1) {
			min = c;
		}
		max = min;
	}
	if (max == -1) {
		maxSquares[x][y] = 0;
		return 0;
	}
	maxSquares[x][y] = max;
	checkAns(max);
	return max;
}

int main() {
	ifstream fin("bigbrn.in");
	fin >> N >> T;
	parcels.resize(N, vector<bool>(N, false));
	maxSquares.resize(N, vector<int>(N, -1));
	for (int i = 0; i < T; i++) {
		pair<int, int> p;
		fin >> p.first >> p.second;
		p.first--;
		p.second--;
		ts.push_back(p);
		parcels[p.first][p.second] = true;
	}
	pair<int, int> tl(-1, -1);
	pair<int, int> br(N, N);
	ts.push_back(tl);
	ts.push_back(br);
	
	findMaxSquareFrom(N - 1, N - 1);

	ofstream fout("bigbrn.out");
	fout << ans << '\n';
}