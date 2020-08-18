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
#include <string.h>

using namespace std;

struct trie_e {
	trie_e* next[10];
	trie_e() {
		memset(next, 0, sizeof(next));
	}
};

int N, tl;
int trieMax = 1;
int square[5][5];
int rowSums[5], colSums[5], diagSums[2];
trie_e trie[100000];
int numOfResults = 0;
int results[10000][5][5];

int findPrimes(int* primes) {
	int nOfPrimes = 0;
	for (int i = 2; i < 100000; i++) {
		bool isPrime = true;
		for (int j = 0; j < nOfPrimes; j++) {
			if (i % primes[j] == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) {
			primes[nOfPrimes++] = i;
		}
	}
	return nOfPrimes;
}

void addToTrie(int prime) {
	int digits[5];
	digits[0] = (prime % 100000) / 10000;
	digits[1] = (prime % 10000) / 1000;
	digits[2] = (prime % 1000) / 100;
	digits[3] = (prime % 100) / 10;
	digits[4] = (prime % 10);
	if (digits[0] + digits[1] + digits[2] + digits[3] + digits[4] != N) {
		return;
	}

	trie_e* next = &trie[0];
	for (int i = 0; i < 5; i++) {
		if (next->next[digits[i]] == 0) {
			next->next[digits[i]] = &trie[trieMax++];
		}
		next = next->next[digits[i]];
	}
}

void setTrie() {
	int primes[100000];
	int numOfPrimes = findPrimes(primes);

	int start;
	for (int i = 0; i < numOfPrimes; i++) {
		if (primes[i] >= 10000) {
			start = i;
			break;
		}
	}

	for (int i = start; i < numOfPrimes; i++) {
		addToTrie(primes[i]);
	}
}

bool checkPrime(int* digits) {
	trie_e* current = &trie[0];
	for (int i = 0; i < 5; i++) {
		if (current->next[digits[i]] == 0) {
			return false;
		}
		current = current->next[digits[i]];
	}
	return true;
}

void verifySquare() {
	int col1[5];
	for (int i = 0; i < 5; i++) {
		col1[i] = square[i][0];
	}
	if (!checkPrime(col1)) {
		return;
	}

	int col5[5];
	for (int i = 0; i < 5; i++) {
		col5[i] = square[i][4];
	}
	if (!checkPrime(col5)) {
		return;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			results[numOfResults][i][j] = square[i][j];
		}
	}
	numOfResults++;
}

void fillRows234(int row) {
	int r = row - 1;
	trie_e* start = &trie[0];
	for (int i = 0; i < 10; i++) {
		if (start->next[i] != 0) {
			square[r][0] = i;
			trie_e* first = start->next[i];
			if (first->next[square[r][1]] == 0) {
				continue;
			}
			trie_e* second = first->next[square[r][1]];
			if (second->next[square[r][2]] == 0) {
				continue;
			}
			trie_e* third = second->next[square[r][2]];
			if (third->next[square[r][3]] == 0) {
				continue;
			}
			trie_e* fourth = third->next[square[r][3]];
			for (int j = 0; j < 10; j++) {
				if (fourth->next[j] != 0) {
					square[r][4] = j;
					if (row == 4) {
						verifySquare();
					}
					else {
						fillRows234(row + 1);
					}
				}
			}
		}
	}
}

void fillCol3() {
	trie_e* first = trie[0].next[square[0][2]];
	for (int i = 0; i < 10; i++) {
		if (first->next[i] != 0) {
			square[1][2] = i;
			trie_e* second = first->next[i];
			if (second->next[square[2][2]] == 0) {
				continue;
			}
			trie_e* third = second->next[square[2][2]];
			for (int j = 0; j < 10; j++) {
				if (third->next[j] != 0) {
					square[3][2] = j;
					trie_e* fourth = third->next[j];
					if (fourth->next[square[4][2]] != 0) {
						fillRows234(2);
					}
				}
			}
		}
	}
}

void fillRow5() {
	trie_e* first = trie[0].next[square[4][0]];
	if (first->next[square[4][1]] == 0){
		return;
	}
	trie_e* second = first->next[square[4][1]];
	for (int i = 0; i < 10; i++) {
		if (second->next[i] != 0) {
			square[4][2] = i;
			trie_e* third = second->next[i];
			if (third->next[square[4][3]] == 0) {
				continue;
			}
			trie_e* fourth = third->next[square[4][3]];
			if (fourth->next[square[4][4]] != 0) {
				fillCol3();
			}
		}
	}
}

void fillCols24(int col) {
	int c = col - 1;
	
	trie_e* first = trie[0].next[square[0][c]];
	if (first->next[square[1][c]] == 0) {
		return;
	}
	trie_e* second = first->next[square[1][c]];
	for (int i = 0; i < 10; i++) {
		if (second->next[i] != 0) {
			square[2][c] = i;
			trie_e* third = second->next[i];
			if (third->next[square[3][c]] == 0) {
				continue;
			}
			trie_e* fourth = third->next[square[3][c]];
			for (int j = 0; j < 10; j++) {
				if (fourth->next[j] != 0) {
					square[4][c] = j;
					if (col == 2) {
						fillCols24(4);
					}
					else {
						fillRow5();
					}
				}
			}
		}
	}
}

void fillRow1() {
	trie_e* start = trie[0].next[square[0][0]];
	for (int i = 1; i < 10; i++) {
		if (start->next[i] != 0) {
			square[0][1] = i;
			trie_e* second = start->next[i];
			for (int j = 1; j < 10; j++) {
				if (second->next[j] != 0) {
					square[0][2] = j;
					trie_e* third = second->next[j];
					for (int k = 1; k < 10; k++) {
						if (third->next[k] != 0) {
							square[0][3] = k;
							trie_e* fourth = third->next[k];
							if (fourth->next[square[0][4]] == 0) {
								continue;
							}
							fillCols24(2);
						}
					}
				}
			}
		}
	}
}

void fillDiag2() {
	trie_e* start = &trie[0];
	for (int i = 1; i < 10; i += 2) {
		if (start->next[i] != 0) {
			square[4][0] = i;
			trie_e* first = start->next[i];
			for (int j = 0; j < 10; j++) {
				if (first->next[j] != 0) {
					square[3][1] = j;
					trie_e* second = first->next[j];
					if (second->next[square[2][2]] == 0) {
						continue;
					}
					trie_e* third = second->next[square[2][2]];
					for (int k = 0; k < 10; k++) {
						if (third->next[k] != 0) {
							square[1][3] = k;
							trie_e* fourth = third->next[k];
							for (int l = 1; l < 10; l++) {
								if (fourth->next[l] != 0) {
									square[0][4] = l;
									fillRow1();
								}
							}
						}
					}
				}
			}
		}
	}
}

void fillDiag1() {
	trie_e* start = trie[0].next[tl];
	for (int i = 0; i < 10; i++) {
		if (start->next[i] != 0) {
			square[1][1] = i;
			trie_e* second = start->next[i];
			for (int j = 0; j < 10; j++) {
				if (second->next[j] != 0) {
					square[2][2] = j;
					trie_e* third = second->next[j];
					for (int k = 0; k < 10; k++) {
						if (third->next[k] != 0) {
							square[3][3] = k;
							trie_e* fourth = third->next[k];
							for (int l = 0; l < 10; l++) {
								if (fourth->next[l] != 0) {
									square[4][4] = l;
									fillDiag2();
								}
							}
						}
					}
				}
			}
		}
	}
}

int compareResults(int a[5][5], int b[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (a[i][j] < b[i][j]) {
				return -1;
			}
			if (a[i][j] > b[i][j]) {
				return 1;
			}
		}
	}
}

void sortResults() {
	for (int i = 0; i < numOfResults - 1; i++) {
		for (int j = i + 1; j < numOfResults; j++) {
			int a = compareResults(results[i], results[j]);
			if (a == 1) {
				int t[5][5];
				for (int k = 0; k < 5; k++) {
					for (int l = 0; l < 5; l++) {
						t[k][l] = results[i][k][l];
					}
				}
				for (int k = 0; k < 5; k++) {
					for (int l = 0; l < 5; l++) {
						results[i][k][l] = results[j][k][l];
					}
				}
				for (int k = 0; k < 5; k++) {
					for (int l = 0; l < 5; l++) {
						results[j][k][l] = t[k][l];
					}
				}
			}
		}
	}
}

void outputResults() {
	sortResults();
	
	ofstream fout("prime3.out");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			fout << results[0][i][j];
		}
		fout << '\n';
	}

	for (int r = 1; r < numOfResults; r++) {
		fout << '\n';
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				fout << results[r][i][j];
			}
			fout << '\n';
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

	setTrie();
	fillDiag1();

	if (numOfResults == 0) {
		ofstream fout("prime3.out");
		fout << "NONE" << '\n';
	}
	else {
		outputResults();
	}
}