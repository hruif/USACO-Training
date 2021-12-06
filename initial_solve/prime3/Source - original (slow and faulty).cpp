/*
ID: ruifanl1
TASK: prime3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <math.h>

using namespace std;

int square[5][5]; // 5x5 square of digits
int single[25]; // single number representing all digits
int rowSums[5], colSums[5], diagSums[2];
int N, tl, nSol; // sum of digits, top left digit, number of solutions
bool formsPrime[10][10][10][10][10];
bool canFormPrime[11][11][11][11];
long long pad;

void outputSolution() {
	static ofstream fout("prime3.out");

	for (int i = 0; i < 25; i++) {
		if (i % 5 == 0) {
			if (nSol > 0 || i != 0) {
				fout << '\n';
			}
		}
		fout << single[i];
	}
	fout << '\n';

	nSol++;
}

bool checkPrime(int index) {
	pad++;
	int row = index / 5;
	int col = index % 5;
	bool fullRow = col == 4;
	bool fullCol = row == 4;
	bool diag1 = fullRow && fullCol;
	bool diag2 = fullCol && col == 0;
	if (fullRow) {
		int p = row * 5;
		int a = single[p];
		int b = single[p + 1];
		int c = single[p + 2];
		int d = single[p + 3];
		int e = single[p + 4];
		if (!formsPrime[a][b][c][d][e]) {
			return false;
		}
	}
	if (fullCol) {
		int a = single[col];
		int b = single[col + 5];
		int c = single[col + 10];
		int d = single[col + 15];
		int e = single[col + 20];
		if (!formsPrime[a][b][c][d][e]) {
			return false;
		}
	}
	if (diag1) {
		int a = single[0];
		int b = single[6];
		int c = single[12];
		int d = single[18];
		int e = single[24];
		if (!formsPrime[a][b][c][d][e]) {
			return false;
		}
	}
	if (diag2) {
		int a = single[20];
		int b = single[16];
		int c = single[12];
		int d = single[8];
		int e = single[4];
		if (!formsPrime[a][b][c][d][e]) {
			return false;
		}
	}
	return true;
}

bool checkCanForm(int index) {
	int row = index / 5;
	int col = index % 5;
	int a = single[row * 5];
	int b = col >= 1 ? single[row * 5 + 1] : 10;
	int c = col >= 2 ? single[row * 5 + 2] : 10;
	int d = col >= 3 ? single[row * 5 + 3] : 10;
	return canFormPrime[a][b][c][d];
}

bool isValid(int index) {

	int r = index / 5;
	int c = index % 5;
	int digit = single[index];
	bool valid = true;
	bool lastInCol = r == 4;
	bool lastInRow = c == 4;
	if (lastInCol && lastInRow) { // if last of diag1
		if (diagSums[0] != N) { // check sum
			return false;
		}
	}
	if (lastInCol) { // if last in column
		if (colSums[c] != N) { // check sum is N
			return false;
		}
		if (digit % 2 == 0) { // check is odd digit
			return false;
		}

		if (c == 0) { // if last in diag2
			if (diagSums[1] != N) { // check sum is N
				return false;
			}
		}
	}
	else { // if not last in column
		if (colSums[c] == N) { // check sum not N
			return false;
		}
		if (r == 3) { // if second to last in column
			int ldC = N - colSums[c];
			if (ldC % 2 == 0) { // check last will be odd
				return false;
			}
			if (ldC >= 10) { // check last can be a single digit
				return false;
			}

			if (c == 1) { // if second to last in diag2
				int ldD2 = N - diagSums[1];
				if (ldD2 % 2 == 0) { // check last will be odd
					return false;
				}
				if (ldD2 >= 10) { // check last can be a single digit
					return false;
				}
			}
		}
	}
	if (lastInRow) { // if last in row
		if (rowSums[r] != N) { // check sum is N
			return false;
		}
		if (digit % 2 == 0) { // check is odd digit
			return false;
		}
	}
	else { // if not last in row
		if (rowSums[r] == N) { // check sum is not N
			return false;
		}
		if (c == 3) { // if second to last in row
			int ldR = N - rowSums[r];
			if (ldR % 2 == 0) { // check last will be odd
				return false;
			}
			if (ldR >= 10) { // check last can be a single digit
				return false;
			}

			if (r == 3) { // if second to last in diag1
				int ldD2 = N - diagSums[0];
				if (ldD2 % 2 == 0) { // check last will be odd
					return false;
				}
				if (ldD2 >= 10) { // check last can be a single digit
					return false;
				}
			}
		}
	}
	if (r == 0 || c == 0) { // if first in row or column
		if (digit == 0) { // check digit is not 0
			return false;
		}
	}
	return checkPrime(index);
}

void addDigit(int index) {
	int r = index / 5;
	int c = index % 5;
	bool diag1 = r == c;
	bool diag2 = abs(r - 4) == c;
	bool canExit = false;
	for (int i = 0; i <= 9; i++) {
		square[r][c] = i;
		rowSums[r] += i;
		colSums[c] += i;
		if (diag1) {
			diagSums[0] += i;
		}
		if (diag2) {
			diagSums[1] += i;
		}
		single[index] = i;
		if (rowSums[r] > N || colSums[c] > N || diagSums[0] > N || diagSums[1] > N) { // if any sum is over N
			canExit = true;
		}
		if (!canExit) {
			if (isValid(index)) {
				if (index == 24) {
					canExit = true; // can only be one solution at this point
					outputSolution();
				}
				else {
					addDigit(index + 1);
				}
			}
		}
		rowSums[r] -= i;
		colSums[c] -= i;
		if (diag1) {
			diagSums[0] -= i;
		}
		if (diag2) {
			diagSums[1] -= i;
		}
		if (canExit) { // return if any sum was over N
			return;
		}
	}
}

void setPrime(int prime) {
	int a = (prime % 100000) / 10000;
	int b = (prime % 10000) / 1000;
	int c = (prime % 1000) / 100;
	int d = (prime % 100) / 10;
	int e = prime % 10;
	formsPrime[a][b][c][d][e] = true;
}

void findPrimes() {
	int primes[100000];
	int nPrimes = 0;
	int num = 2;
	while (num < 100000) {
		bool isPrime = true;
		for (int i = 0; i < nPrimes; i++) {
			if (num % primes[i] == 0) {
				isPrime = false;
				break;
			}
			if (sqrt(num) < primes[i]) {
				break;
			}
		}
		if (isPrime) {
			setPrime(num);
			primes[nPrimes++] = num;
		}
		num++;
	}
}

void setFormPrimes() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 11; j++) {
			if (j == 10) {
				bool hasPrime = false;
				for (int k = 0; k < 10; k++) {
					if (canFormPrime[i][k][10][10]) {
						hasPrime = true;
						break;
					}
				}
				if (hasPrime) {
					canFormPrime[i][j][10][10] = true;
				}
				break;
			}
			for (int k = 0; k < 11; k++) {
				if (k == 10) {
					bool hasPrime = false;
					for (int l = 0; l < 10; l++) {
						if (canFormPrime[i][j][l][10]) {
							hasPrime = true;
							break;
						}
					}
					if (hasPrime) {
						canFormPrime[i][j][k][10] = true;
					}
					break;
				}
				for (int l = 0; l < 11; l++) {
					if (l == 10) {
						bool hasPrime = false;
						for (int p = 0; p < 10; p++) {
							if (canFormPrime[i][j][k][p]) {
								hasPrime = true;
								break;
							}
						}
						if (hasPrime) {
							canFormPrime[i][j][k][l] = true;
						}
						break;
					}
					bool hasPrime = false;
					for (int p = 0; p < 10; p++) {
						if (formsPrime[i][j][k][l][p]) {
							hasPrime = true;
							break;
						}
					}
					if (hasPrime) {
						canFormPrime[i][j][k][l] = true;
					}
				}
			}
		}
	}
}

int main() {
	ifstream fin("prime3.in");
	fin >> N >> tl;
	square[0][0] = tl;
	rowSums[0] += tl;
	colSums[0] += tl;
	diagSums[0] += tl;
	single[0] = 1;

	findPrimes();
	setFormPrimes();
	addDigit(1);

	if (nSol == 0) {
		ofstream fout("prime3.out");
		fout << "NONE" << '\n';
	}
}