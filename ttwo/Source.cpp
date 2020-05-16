/*
ID: ruifanl1
TASK: ttwo
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int minutes;
bool visited[2][10][10][4]; // john and cows, rows, columns, direction
char grid[10][10];

void move(int& face, int* mover, char letter) {
	bool rotate = false;
	int x = mover[0], y = mover[1];
	if (face == 0) {
		if (x == 0 || grid[x - 1][y] == '*') {
			rotate = true;
		}
	}
	if (face == 1) {
		if (y == 9 || grid[x][y + 1] == '*') {
			rotate = true;
		}
	}
	if (face == 2) {
		if (x == 9 || grid[x + 1][y] == '*') {
			rotate = true;
		}
	}
	if (face == 3) {
		if (y == 0 || grid[x][y - 1] == '*') {
			rotate = true;
		}
	}
	if (rotate) {
		face += 1;
		face %= 4;
	}
	else {
		if (face == 0) {
			grid[mover[0]--][mover[1]] = '.';
			grid[mover[0]][mover[1]] = letter;
		}
		if (face == 1) {
			grid[mover[0]][mover[1]++] = '.';
			grid[mover[0]][mover[1]] = letter;
		}
		if (face == 2) {
			grid[mover[0]++][mover[1]] = '.';
			grid[mover[0]][mover[1]] = letter;
		}
		if (face == 3) {
			grid[mover[0]][mover[1]--] = '.';
			grid[mover[0]][mover[1]] = letter;
		}
	}
}

bool solve(int john[], int cows[]) {
	int cowFace = 0, johnFace = 0;
	while (true) {
		move(johnFace, john, 'F');
		move(cowFace, cows, 'C');
		minutes++;
		if (john[0] == cows[0] && john[1] == cows[1]) {
			return false;
		}
		if (minutes > 10000) {
			return true;
		}
	}
}

int main() {
	ifstream fin("ttwo.in");
	int john[2], cows[2];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			char tmp;
			fin >> tmp;
			if (tmp == 'F') {
				john[0] = i;
				john[1] = j;
			}
			if (tmp == 'C') {
				cows[0] = i;
				cows[1] = j;
			}
			grid[i][j] = tmp;
		}
	}

	bool infinite = solve(john, cows);


	ofstream fout("ttwo.out");
	if (infinite) {
		fout << 0;
	}
	else {
		fout << minutes;
	}
	fout << '\n';
}