/*
ID: ruifanl1
TASK: game1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Scores
{
	int score1;
	int score2;
	Scores(int a, int b) {
		score1 = a;
		score2 = b;
	}
	Scores() {

	}
};

int N;
int B[100];
Scores cache[100][100];
bool flags[100][100];

Scores findBestScores(int l, int r) {
	if (flags[l][r]) {
		return cache[l][r];
	}
	if (l == r) {
		Scores result(B[l], 0);
		cache[l][r] = result;
		flags[l][r] = true;
		return result;
	}
	Scores a = findBestScores(l + 1, r);
	Scores b = findBestScores(l, r - 1);
	int s1 = a.score2 + B[l];
	int s2 = b.score2 + B[r];
	if (s1 > s2) {
		Scores result(s1, a.score1);
		cache[l][r] = result;
		flags[l][r] = true;
		return result;
	}
	else {
		Scores result(s2, b.score1);
		cache[l][r] = result;
		flags[l][r] = true;
		return result;
	}
}

int main() {
	ifstream fin("game1.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> B[i];
	}

	Scores ans = findBestScores(0, N - 1);

	ofstream fout("game1.out");
	fout << ans.score1 << ' ' << ans.score2 << '\n';
	fout.close();
}