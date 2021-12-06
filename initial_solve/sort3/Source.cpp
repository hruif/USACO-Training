/*
ID: ruifanl1
TASK: sort3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, ones, twos, threes;
vector<int> keyVals;


int countSwaps() {
	int swaps = 0;
	int bad1 = 0;
	int bad2 = 0;
	int bad3 = 0;
	for (int i = 0; i < ones; i++) {
		if (keyVals[i] == 2) {
			bad2++;
		}
		if (keyVals[i] == 3) {
			bad3++;
		}
	}
	for (int i = ones; i < ones + twos; i++) {
		if (keyVals[i] == 1) {
			bad1++;
		}
	}
	while (bad1 > 0 && bad2 > 0) {
		swaps++;
		bad1--;
		bad2--;
	}
	int badNum = bad1 > bad2 ? bad1 : bad2;
	bad1 = 0;
	bad2 = 0;

	for (int i = ones + twos; i < ones + twos + threes; i++) {
		if (keyVals[i] == 1) {
			bad1++;
		}
	}
	while (bad1 > 0 && bad3 > 0) {
		swaps++;
		bad1--;
		bad3--;
	}
	bad3 = 0;

	for (int i = ones; i < ones + twos; i++) {
		if (keyVals[i] == 3) {
			bad3++;
		}
	}
	for (int i = ones + twos; i < ones + twos + threes; i++) {
		if (keyVals[i] == 2) {
			bad2++;
		}
	}
	while (bad2 > 0 && bad3 > 0) {
		swaps++;
		bad2--;
		bad3--;
	}

	swaps += badNum * 2;
	return swaps;
}

int main() {
	ifstream fin("sort3.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		fin >> tmp;
		keyVals.push_back(tmp);
		if (tmp == 1) {
			ones++;
		}
		if (tmp == 2) {
			twos++;
		}
		if (tmp == 3) {
			threes++;
		}
	}

	int ans = countSwaps();
	ofstream fout("sort3.out");
	fout << ans << '\n';
}