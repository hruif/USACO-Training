/*
ID: ruifanl1
TASK: latin
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

int N;
bool rows[7][7], cols[7][7];
unordered_map<string, long long> cache;

string stateToString() { // converts farm to state into a string for caching
	string s;
	for (int i = 0; i < N; i++) {
		s.push_back('c');
		for (int j = 0; j < N; j++) {
			if (cols[i][j]) {
				s.push_back(j + '0');
			}
		}
	}
	return s;
}

long long findLatin(int x, int y) {
	if (y == N) {
		y = 0;
		x++;
		if (x == N) {
			return 1;
		}
	}

	string s = stateToString();
	if (cache.find(s) != cache.end()) {
		return cache[s];
	}

	long long latins = 0;
	for (int i = 0; i < N; i++) {
		if (!rows[x][i] && !cols[y][i]) {
			rows[x][i] = true;
			cols[y][i] = true;
			latins += findLatin(x, y + 1);
			rows[x][i] = false;
			cols[y][i] = false;
		}
	}

	cache[s] = latins;
	return latins;
}

int main() {
	ifstream fin("latin.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		rows[0][i] = true;
		cols[i][i] = true;
	}

	long long ans = findLatin(1, 0);

	ofstream fout("latin.out");
	fout << ans << '\n';
}