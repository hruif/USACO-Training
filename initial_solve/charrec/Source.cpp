/*
ID: ruifanl1
TASK: charrec
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Decorrupted {
	vector<char> s;
	int corruptions;
	Decorrupted() {
		corruptions = -2;
	}
};

int N;
char ideals[27][20][20];
vector<Decorrupted> cache;
vector<vector<char>> corrupted;

Decorrupted score(int a, int b) {
	Decorrupted best;
	best.s.resize(1);
	bool ignore = false;
	bool ignoreTwo = false;
	if (b - a == 19) {
		ignore = true;
	}
	else if (b - a == 21) {
		ignore = true;
		ignoreTwo = true;
	}

	for (int l = 0; l < 27; l++) {
		for (int i = 0; i < 20; i++) {
			int score = 0;
			if (!ignore) { // if none to be ignored, set i to 20
				i = 20;
			}
			for (int j = 0; j < 20; j++) {
				int line = a + j;
				if (ignore) {
					if (j == i) { // if line is one to be ignored, continue
						continue;
						score++;
					}
					if (j > i) {
						if (ignoreTwo) { // if there is a duplicate, add one to account for it
							line++;
						}
						else { // if there is a missing, subtract one to account for it
							line--;
						}
					}
				}

				for (int k = 0; k < 20; k++) {
					if (corrupted[line][k] != ideals[l][j][k]) { // add one to score for every different digit
						score++;
					}
				}
			}
			if (ignoreTwo) { // find least corrupted of duplicate pair
				int s1 = 0;
				int s2 = 0;
				for (int j = 0; j < 20; j++) {
					if (corrupted[a + i][j] != ideals[l][i][j]) {
						s1++;
					}
				}
				for (int j = 0; j < 20; j++) {
					if (corrupted[a + i + 1][j] != ideals[l][i][j]) {
						s2++;
					}
				}
				score += s1 < s2 ? s1 : s2;
			}
			if (score < best.corruptions || best.corruptions == -2) { // set best score
				if (l == 0) {
					best.s[0] = ' ';
				}
				else {
					best.s[0] = l - 1 + 'a';
				}
				best.corruptions = score;
			}
		}
	}
	return best;
}

Decorrupted find(int a) { // best string and number of corruptions
	if (a == 0) {
		Decorrupted t;
		t.corruptions = 0;
		return t;
	}
	if (cache[a].corruptions != -2) {
		return cache[a];
	}
	if (a - 19 < 0) {
		Decorrupted t;
		t.corruptions = -1;
		cache[a] = t;
		return t;
	}
	Decorrupted best;

	Decorrupted missing = find(a - 19);
	Decorrupted normal;
	if (a - 20 >= 0) {
		normal = find(a - 20);
	}
	Decorrupted duplicated;
	if (a - 21 >= 0) {
		duplicated = find(a - 21);
	}
	if (missing.corruptions == -1 && normal.corruptions == -1 && duplicated.corruptions == -1) {
		cache[a] = normal;
		return normal;
	}

	Decorrupted currentM;
	if (missing.corruptions != -1) {
		currentM = score(a - 19, a);
		if (currentM.corruptions > 121) {
			missing.s.push_back('?');
		}
		else {
			missing.s.push_back(currentM.s[0]);
		}
		missing.corruptions += currentM.corruptions;
	}
	Decorrupted currentN;
	if (normal.corruptions != -1 && a - 20 >= 0) {
		currentN = score(a - 20, a);
		if (currentN.corruptions > 120) {
			normal.s.push_back('?');
		}
		else {
			normal.s.push_back(currentN.s[0]);
		}
		normal.corruptions += currentN.corruptions;
	}
	Decorrupted currentD;
	if (duplicated.corruptions != -1 && a - 21 >= 0) {
		currentD = score(a - 21, a);
		if (currentD.corruptions > 121) {
			duplicated.s.push_back('?');
		}
		else {
			duplicated.s.push_back(currentD.s[0]);
		}
		duplicated.corruptions += currentD.corruptions;
	}

	best = missing;
	if (normal.corruptions != -1 && normal.corruptions != -2 && (best.corruptions > normal.corruptions || best.corruptions < 0)) {
		best.s = normal.s;
		best.corruptions = normal.corruptions;
	}
	if (duplicated.corruptions != -1 && duplicated.corruptions != -2 && (best.corruptions > duplicated.corruptions || best.corruptions < 0)) {
		best.s = duplicated.s;
		best.corruptions = duplicated.corruptions;
	}
	cache[a] = best;
	return best;
}

int main() {
	ifstream fontFin("font.in");
	ifstream fin("charrec.in");
	int fontN;
	fontFin >> fontN;
	for (int i = 0; i < fontN; i++) {
		for (int j = 0; j < 20; j++) {
			char c;
			fontFin >> c;
			ideals[i / 20][i % 20][j] = c;
		}
	}

	fin >> N;
	cache.resize(N + 1);
	corrupted.resize(N, vector<char>(20));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 20; j++) {
			char c;
			fin >> c;
			corrupted[i][j] = c;
		}
	}

	find(N);

	ofstream fout("charrec.out");
	for (int i = 0; i < cache[N].s.size(); i++) {
		fout << cache[N].s[i];
	}
	fout << '\n';
}