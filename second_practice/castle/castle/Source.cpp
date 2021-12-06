/*
ID: ruifan1
TASK: castle
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

int M, N;
int castle[50][50];
int rsizes[50][50];
int rids[50][50];
bool visited[50][50];

queue<pair<int, int>> q;
void check_castle(int x, int y) {
	q.push({ x, y });
	visited[x][y] = true;
	if (x > 0 && !(castle[x][y] & 2) && !visited[x - 1][y]) check_castle(x - 1, y);
	if (y < M - 1 && !(castle[x][y] & 4) && !visited[x][y + 1]) check_castle(x, y + 1);
	if (x < N - 1 && !(castle[x][y] & 8) && !visited[x + 1][y]) check_castle(x + 1, y);
	if (y > 0 && !(castle[x][y] & 1) && !visited[x][y - 1]) check_castle(x, y - 1);
}

int main() {
	ifstream fin("castle.in");
	ofstream fout("castle.out");

	fin >> M >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) fin >> castle[i][j];
	}
	int rid = 0, msize = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!visited[i][j]) {
				check_castle(i, j);
				int rsize = q.size();
				msize = max(msize, rsize);
				while (!q.empty()) {
					int x = q.front().first, y = q.front().second;
					q.pop();
					rsizes[x][y] = rsize;
					rids[x][y] = rid;
				}
				rid++;
			}
		}
	}

	int bigS = 0, bigWD;
	pair<int, int> bigW;
	for (int j = 0; j < M; j++) {
		for (int i = N - 1; i >= 0; i--) {
			if ((castle[i][j] & 2) && i > 0 && rids[i][j] != rids[i - 1][j]) {
				int nrsize = rsizes[i][j] + rsizes[i - 1][j];
				if (nrsize > bigS) {
					bigS = nrsize;
					bigWD = 2;
					bigW = { i, j };
				}
			}
			if ((castle[i][j] & 4) && j < M - 1 && rids[i][j] != rids[i][j + 1]) {
				int nrsize = rsizes[i][j] + rsizes[i][j + 1];
				if (nrsize > bigS) {
					bigS = nrsize;
					bigWD = 4;
					bigW = { i, j };
				}
			}
			//if ((castle[i][j] & 8) && i < N - 1 && rids[i][j] != rids[i + 1][j]) {
			//	int nrsize = rsizes[i][j] + rsizes[i + 1][j];
			//	if (nrsize > bigS) {
			//		bigS = nrsize;
			//		bigWD = 8;
			//		bigW = { i, j };
			//	}
			//}
			//if ((castle[i][j] & 1) && j > 0 && rids[i][j] != rids[i][j - 1]) {
			//	int nrsize = rsizes[i][j] + rsizes[i][j - 1];
			//	if (nrsize > bigS) {
			//		bigS = nrsize;
			//		bigWD = 1;
			//		bigW = { i, j };
			//	}
			//}
		}
	}

	fout << rid << '\n';
	fout << msize << '\n';
	fout << bigS << '\n';
	fout << bigW.first + 1 << ' ' << bigW.second + 1 << ' ';
	if (bigWD == 2) fout << "N\n";
	else fout << "E\n";
}