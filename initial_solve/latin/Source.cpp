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
			if (!cols[i][j]) {
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

	/*string s = stateToString();
	if (cache.find(s) != cache.end()) {
		return cache[s];
	}*/

	if (y == 0) {
		rows[x][x] = true;
		cols[0][x] = true;
		long long latins = findLatin(x, y + 1);
		rows[x][x] = false;
		cols[0][x] = false;
		return latins;
	}
	if (x == 1) {
		long long latins = 0;
		long long latinsz = 0;

		for (int i = 0; i < y; i++) {
			if (!rows[x][i]) {
				rows[x][i] = true;
				cols[y][i] = true;
				latinsz = findLatin(x, y + 1);
				rows[x][i] = false;
				cols[y][i] = false;
			}
		}
		int lasti = 0;
		for (int i = y + 1; i < N; i++) {
			if (!rows[x][i] && !cols[y][i]) {
				rows[x][i] = true;
				cols[y][i] = true;
				long long nwlatins = findLatin(x, y + 1);
				if (latins == 0) {
					latins = nwlatins;
					lasti = i;
				}
				if (nwlatins != latins) {
					int a = 5;
				}
				rows[x][i] = false;
				cols[y][i] = false;
				break;
			}
		}
		long long total = latinsz;
		for (int i = y + 1; i < N; i++) {
			if (!rows[x][i] && !cols[y][i]) {
				total += latins;
			}
		}

		/*
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < N; j++) {
				if (cols[i][j]) {
					cout << j;
				}
			}
			cout << endl;
		}
		cout << total << "\n\n";
		*/

		return total;
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

	//cache[s] = latins;
	return latins;
}

long long f() {
	long long val = 1;
	for (long long i = 1; i < N; i++) {
		val *= i;
	}
	return val;
}

int main() {
	ifstream fin("latin.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		rows[0][i] = true;
		cols[i][i] = true;
	}

	long long ans = findLatin(1, 0) * f();

	ofstream fout("latin.out");
	fout << ans << '\n';
}