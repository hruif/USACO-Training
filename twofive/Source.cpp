/*
ID: ruifanl1
TASK: twofive
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

char task;
int M;
char endState[25];
int found[6][6][6][6][6];
char prefix[25];

bool isValid(int x, int y, char letter) {
	int index = x * 5 + y;
	if (prefix[index] >= 0 && prefix[index] != letter) {
		return false;
	}
	return true;
}

int find(int a, int b, int c, int d, int e, char letter) {
	if (e == 5) {
		return 1;
	}
	if (found[a][b][c][d][e] >= 0) {
		return found[a][b][c][d][e];
	}
	int sum = 0;
	if (a < 5 && isValid(0, a, letter)) {
		sum += find(a + 1, b, c, d, e, letter + 1);
	}
	if (b < a && isValid(1, b, letter)) {
		sum += find(a, b + 1, c, d, e, letter + 1);
	}
	if (c < b && isValid(2, c, letter)) {
		sum += find(a, b, c + 1, d, e, letter + 1);
	}
	if (d < c && isValid(3, d, letter)) {
		sum += find(a, b, c, d + 1, e, letter + 1);
	}
	if (e < d && isValid(4, e, letter)) {
		sum += find(a, b, c, d, e + 1, letter + 1);
	}

	found[a][b][c][d][e] = sum;
	return sum;
}

void solve() {
	memset(prefix, -1, sizeof(prefix));
	if (task == 'N') {
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++) {
				prefix[i] = j + 'A';
				memset(found, -1, sizeof(found));
				int t = find(0, 0, 0, 0, 0, 'A');
				if (t >= M) {
					break;
				}
				M -= t;
				prefix[i] = -1;
			}
		}
	}
	else {
		// task == 'W'
		M = 0;
		prefix[0] = 'A';
		for (int i = 1; i < 24; i++) {
			for (int j = 1; j < endState[i] - 'A'; j++) {
				prefix[i] = j + 'A';
				memset(found, -1, sizeof(found));
				int t = find(0, 0, 0, 0, 0, 'A');
				M += t;
			}
			prefix[i] = endState[i];
		}
		M++;
	}
}

int main() {
	memset(found, -1, sizeof(found));
	ifstream fin("twofive.in");
	fin >> task;
	if (task == 'N') {
		fin >> M;
	}
	else {
		for (int i = 0; i < 25; i++) {
			fin >> endState[i];
		}
	}

	solve();

	ofstream fout("twofive.out");
	if (task == 'W') {
		fout << M;
	}
	else {
		for (int i = 0; i < 25; i++) {
			fout << prefix[i];
		}
	}
	fout << '\n';
}