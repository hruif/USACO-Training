/*
ID: ruifanl1
TASK: checker
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int N;
int ans = 0;
int placed[13];
int firstThree[3][13];

void fillSquare(int r, int c, int d1, int d2) {
	if (r == N) {
		if (ans < 3) {
			for (int i = 0; i < N; i++) {
				firstThree[ans][i] = placed[i];
			}
		}
		ans++;
		return;
	}

	d1 >>= 1;
	d2 <<= 1;

	int canVisit = c | d1 | d2;
	int b = 1;
	for (int i = 0; i < N; i++, b <<= 1) {
		if (!(b & canVisit)) {
			placed[r] = i;
			int newc = c | b;
			int newd1 = d1 | b;
			int newd2 = d2 | b;
			fillSquare(r + 1, newc, newd1, newd2);
		}
	}
}

int main() {
	ifstream fin("checker.in");
	fin >> N;

	fillSquare(0, 0, 0, 0);

	ofstream fout("checker.out");
	for (int i = 0; i < 3; i++) {
		fout << firstThree[i][0] + 1;
		for (int j = 1; j < N; j++) {
			fout << ' ' << firstThree[i][j] + 1;
		}
		fout << '\n';
	}
	fout << ans << '\n';
}