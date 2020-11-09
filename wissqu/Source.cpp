/*
ID: ruifanl1
TASK: wissqu
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <string.h>

using namespace std;

int steps[16][2];
string farm;
unordered_map<string, int> cache;
bool replaced[16];
int total = 0;

bool foundSol = false;
int firstSolSteps[16][2];

bool findLetter(int r, int c, int letter) {
	if (r < 0 || r > 3) {
		return false;
	}
	if (c < 0 || c > 3) {
		return false;
	}
	return farm[r * 4 + c] - 'A' == letter;
}

bool canPlace(int index, int letter) {
	int r = index / 4;
	int c = index % 4;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (findLetter(r + i, c + j, letter)) {
				return false;
			}
		}
	}
	return true;
}

void replaceFirstSol() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 2; j++) {
			firstSolSteps[i][j] = steps[i][j];
		}
	}
}

void updateFirst() {
	if (!foundSol) {
		foundSol = true;
		replaceFirstSol();
		return;
	}

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 2; j++) {
			if (firstSolSteps[i][j] < steps[i][j]) {
				return;
			}
			if (firstSolSteps[i][j] > steps[i][j]) {
				replaceFirstSol();
				return;
			}
		}
	}
}

int addCow(int* remaining, int step) {
	if (step == 16) {
		updateFirst();
		return 1;
	}

	int total = 0;
	string farm0 = farm;
	if (cache.find(farm) != cache.end()) {
		total = cache[farm];
		return total;
	}
	for (int j = 0; j < 5; j++) {
		if (remaining[j] == 0) {
			continue;
		}
		for (int i = 0; i < 16; i++) {
			if (replaced[i]) {
				continue;
			}
			int original = farm[i] - 'A';
			replaced[i] = true;
			if (canPlace(i, j)) {
				remaining[j]--;
				steps[step][0] = j;
				steps[step][1] = i;
				farm[i] = j + 'A';
				total += addCow(remaining, step + 1);
				remaining[j]++;
				farm[i] = original + 'A';
			}
			replaced[i] = false;
		}
	}
	//cache.insert({ farm, total });
	cache[farm] = total;
	return total;
}

int main() {
	memset(replaced, false, sizeof(replaced));

	ifstream fin("wissqu.in");
	for (int i = 0; i < 16; i++) {
		char t;
		fin >> t;
		farm.push_back(t);
	}

	int remaining[5] = { 3, 3, 3, 4, 3 };
	int total = addCow(remaining, 0);

	ofstream fout("wissqu.out");
	for (int i = 0; i < 16; i++) {
		char l = firstSolSteps[i][0] + 'A';
		int r = firstSolSteps[i][1] / 4 + 1;
		int c = firstSolSteps[i][1] % 4 + 1;
		fout << l << ' ' << r << ' ' << c << '\n';
	}
	fout << total << '\n';
}