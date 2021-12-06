/*
ID: ruifanl1
TASK: ratios
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int goal[3], A[3], B[3], C[3];

int findMax(int* mixture) {
	int least = -1;
	for (int i = 0; i < 3; i++) {
		if (mixture[i] == 0) {
			continue;
		}
		int maxMix = 100 / mixture[i];
		if (least == -1 || maxMix < least) {
			least = maxMix;
		}
	}
	return least;
}

void addTo(int* test, int* mixture, int x) {
	for (int i = 0; i < 3; i++) {
		test[i] += mixture[i] * x;
	}
}

bool isRatio(int* test) {
	for (int i = 0; i < 3; i++) {
		if (goal[i] == 0) {
			if (test[i] == 0) {
				continue;
			}
			else {
				return false;
			}
		}
		if (test[i] % goal[i] != 0) {
			return false;
		}
	}
	if (goal[0] != 0 && goal[1] != 0) {
		if (test[0] / goal[0] != test[1] / goal[1]) {
			return false;
		}
	}
	if (goal[1] != 0 && goal[2] != 0) {
		if (test[1] / goal[1] != test[2] / goal[2]) {
			return false;
		}
	}
	if (goal[2] != 0 && goal[0] != 0) {
		if (test[2] / goal[2] != test[0] / goal[0]) {
			return false;
		}
	}
	return true;
}

bool over100(int* test) {
	for (int i = 0; i < 3; i++) {
		if (test[i] >= 100) {
			return true;
		}
	}
	return false;
}

bool solve(int* ans) {
	int test[3] = { 0, 0, 0 };
	int bestRatio[3] = { -1, -1, -1 };
	bool solvable = false;
	for (int a = 0; a < 100; a++) {
		addTo(test, A, a);

		for (int b = 0; b < 100; b++) {
			addTo(test, B, b);

			for (int c = 0; c < 100; c++) {
				addTo(test, C, c);
				int usedFeed = a + b + c;
				if (usedFeed == 0) {
					continue;
				}

				if (isRatio(test)) {
					if (test[0] < bestRatio[0] || bestRatio[0] == -1) {
						solvable = true;
						for (int i = 0; i < 3; i++) {
							bestRatio[i] = test[i];
						}
						ans[0] = a;
						ans[1] = b;
						ans[2] = c;
						ans[3] = test[0] / goal[0];
					}
				}

				addTo(test, C, -c);
			}

			addTo(test, B, -b);
		}

		addTo(test, A, -a);
	}

	return solvable;
}

int main() {
	ifstream fin("ratios.in");
	fin >> goal[0] >> goal[1] >> goal[2];
	fin >> A[0] >> A[1] >> A[2];
	fin >> B[0] >> B[1] >> B[2];
	fin >> C[0] >> C[1] >> C[2];

	int ans[4] = { -1, -1, -1, -1 };

	ofstream fout("ratios.out");
	if (solve(ans)) {
		fout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << ' ' << ans[3] << '\n';
	}
	else {
		fout << "NONE" << '\n';
	}
}