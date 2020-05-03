/*
ID: ruifanl1
TASK: prefix
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string S;
vector<string> primitives;
vector<int> results;

int solve(int k) {
	if (k == 0) {
		results[k] = 0;
		return 0;
	}
	if (results[k] != -2) {
		return results[k];
	}
	for (int i = 0; i < primitives.size(); i++) {
		if (k >= primitives[i].size()) {
			bool match = true;
			for (int j = 0; j < primitives[i].size(); j++) {
				if (primitives[i][j] != S[k - primitives[i].size() + j]) {
					match = false;
					break;
				}
			}
			if (match && results[k - primitives[i].size()] >= 0) {
				results[k] = k;
				return k;
			}
		}
	}
	results[k] = -1;
	return -1;
}

int main() {
	ifstream fin("prefix.in");

	char word[100];
	int count = 0;
	while (true) {
		fin >> word;
		if (word[0] == '.' && word[1] == 0) {
			break;
		}
		primitives.push_back(word);
	}
	while (fin >> word) {
		S.append(word);
	}

	results.resize(S.size() + 1, -2);
	int maxLength = 0;
	for (int k = 0; k <= S.size(); k++) {
		maxLength = max(maxLength, solve(k));
	}

	ofstream fout("prefix.out");
	fout << maxLength << '\n';
}