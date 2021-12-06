/*
ID: ruifanl1
TASK: maze1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int W, H, exits[2][2];
vector<vector<int>> dist; // how many steps away it is from source
vector<string> maze;
vector<vector<bool>> north, east, south, west;

void findExits() {
	int found = 0;
	for (int i = 1; i <= W; i++) {
		int x = i * 2 - 1;
		if (maze[0][x] == ' ') {
			exits[found][1] = x;
			exits[found][0] = 1;
			found++;
		}
		if (maze[H * 2][x] == ' ') {
			exits[found][1] = x;
			exits[found][0] = H * 2 - 1;
			found++;
		}
	}
	for (int i = 1; i <= H; i++) {
		int y = i * 2 - 1;
		if (maze[y][0] == ' ') {
			exits[found][1] = 1;
			exits[found][0] = y;
			found++;
		}
		if (maze[y][W * 2] == ' ') {
			exits[found][1] = W * 2 - 1;
			exits[found][0] = y;
			found++;
		}
	}
}

void findPaths(int row, int column, int steps) {
	if (dist[row][column] <= steps && dist[row][column] >= 0) {
		return;
	}
	dist[row][column] = steps;
	steps++;
	if (row > 1) {
		if (maze[row - 1][column] == ' ') {
			findPaths(row - 2, column, steps);
		}
	}
	if (row < H * 2 - 1) {
		if (maze[row + 1][column] == ' ') {
			findPaths(row + 2, column, steps);
		}
	}
	if (column > 1) {
		if (maze[row][column - 1] == ' ') {
			findPaths(row, column - 2, steps);
		}
	}
	if (column < W * 2 - 1) {
		if (maze[row][column + 1] == ' ') {
			findPaths(row, column + 2, steps);
		}
	}
}

int main() {
	ifstream fin("maze1.in");
	fin >> W >> H;
	string blank;
	getline(fin, blank);
	for (int i = 0; i < H * 2 + 1; i++) {
		string buff;
		getline(fin, buff);
		maze.push_back(buff);
		vector<int> row(W * 2 + 1, -1);
		dist.push_back(row);
	}

	findExits();
	findPaths(exits[0][0], exits[0][1], 0);
	findPaths(exits[1][0], exits[1][1], 0);

	int ans = 0;
	for (int i = 1; i < H * 2 + 1; i += 2) {
		for (int j = 1; j < W * 2 + 1; j += 2) {
			ans = dist[i][j] > ans ? dist[i][j] : ans;
		}
	}
	ofstream fout("maze1.out");
	fout << ans + 1 << '\n';
}