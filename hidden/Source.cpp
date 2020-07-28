/*
ID: ruifanl1
TASK: hidden
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int L;
vector<char> S;

int checkBorders(int i) {
	if (i >= L) {
		i = i - L;
	}
	return i;
}

void removeBad(vector<int>& starts, int len) {
	for (int i = starts.size() - 1; i > 0; i--) {
		if (starts[i] - len <= starts[i - 1]) {
			starts.erase(starts.begin() + i);
		}
	}
}

int findAns() {
	int len = 0;
	vector<int> starts;
	for (int i = 0; i < L; i++) {
		starts.push_back(i);
	}
	while (starts.size() != 1) {
		vector<int> newStarts;
		char best = -1;
		for (int i = 0; i < starts.size(); i++) {
			int index = checkBorders(starts[i] + len);
			if (S[index] - 'a' < best || best == -1) {
				newStarts.clear();
				newStarts.push_back(starts[i]);
				best = S[index] - 'a';
			}
			else if (S[index] - 'a' == best) {
				newStarts.push_back(starts[i]);
			}
		}
		starts = move(newStarts);
		if (starts.size() == L) {
			return 0;
		}
		removeBad(starts, len);
		len++;
	}
	return starts[0];
}

int main() {
	ifstream fin("hidden.in");
	fin >> L;
	for (int i = 0; i < L; i++) {
		char t;
		fin >> t;
		S.push_back(t);
	}

	int ans = findAns();

	ofstream fout("hidden.out");
	fout << ans << '\n';
}