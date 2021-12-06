/*
ID: ruifanl1
TASK: kimbits
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, L;
unsigned int I;
unsigned int F[32][32];

void calculate(int n, int l) {
	if (l == 0) {
		F[n][l] = 1;
		return;
	}
	if (l == 1) {
		F[n][l] = n + 1;
		return;
	}
	// l > 1
	if (n == 1) {
		F[n][l] = 2;
		return;
	}
	// n > 1
	F[n][l] = F[n - 1][l] + F[n - 1][l - 1];
}

int main() {
	ifstream fin("kimbits.in");
	fin >> N >> L >> I;

	// 1. calculate F
	for (int n = 1; n <= N; n++) {
		for (int l = 0; l <= L; l++) {
			calculate(n, l);
		}
	}

	// 2. locate Ith item
	unsigned int l = L;
	unsigned int i = I;
	unsigned int x = 0;
	for (int n = N; n >= 1; n--) {
		int b = 1 << (n - 1);
		if (n == 1) {
			if (i == 2) {
				x = x | b;
			}
			continue;
		}
		if (F[n - 1][l] >= i) {
			// bit n is 0
			continue;
		}
		else {
			// bit n is 1
			x = x | b;
			i -= F[n - 1][l];
			if (i == 1) {
				break;
			}
			l--;
		}
	}

	ofstream fout("kimbits.out");

	for (int n = N; n >= 1; n--) {
		int b = 1 << (n - 1);
		if ((b & x) != 0) {
			fout << '1';
		}
		else {
			fout << '0';
		}
	}

	fout << '\n';
}