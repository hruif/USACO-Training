/*
ID: ruifanl1
TASK: cowxor
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int N, best;
pair<int, int> ans;
vector<int> input;
vector<int> xors;
vector<bool> isXor;
vector<pair<int, int>> trie;

void addToTrie(int index) {
	int num = xors[index];
	int b = (1 << 20);
	int current = 0;
	int currentNum = 0;
	for (int i = 0; i < 21; i++) {
		bool bit = b & num;
		if (bit) {
			if (trie[current].first == -1) {
				trie[current].first = trie.size();
				trie.push_back(move(pair<int, int>(-1, -1)));
				isXor.push_back(false);
			}
			current = trie[current].first;
			currentNum |= b;
		}
		else {
			if (trie[current].second == -1) {
				trie[current].second = trie.size();
				trie.push_back(move(pair<int, int>(-1, -1)));
				isXor.push_back(false);
			}
			current = trie[current].second;
		}
		if (currentNum == num) {
			isXor[current] = true;
			return;
		}
		b >>= 1;
	}
}

void findXors() {
	xors.resize(N);
	xors[0] = input[0];
	for (int i = 1; i < N; i++) {
		xors[i] = input[i] ^ xors[i - 1];
	}
}

void solve() {
	int max_i = -1;
	int max_xj = -1;
	int max_value = -1;
	for (int i = 0; i < N; i++) {
		addToTrie(i);
		int b = (1 << 20);
		int xi = xors[i];
		int current = 0;
		int xj = 0;

		if (max_value == -1 || max_value < xi) {
			max_value = xi;
			max_i = i;
			max_xj = xi;
		}

		for (int j = 0; j < 21; j++) {
			bool bit = xi & b;
			if (!bit) {
				if (trie[current].first == -1) {
					if (trie[current].second == -1) {
						break;
					}
					current = trie[current].second;
				}
				else {
					current = trie[current].first;
					xj |= b;
				}
			}
			else {
				if (trie[current].second == -1) {
					if (isXor[current]) {
						break;
					}
					current = trie[current].first;
					xj |= b;
				}
				else {
					current = trie[current].second;
				}
			}
			b >>= 1;
		}
		if (max_value == -1 || max_value < (xi ^ xj)) {
			max_value = xi ^ xj;
			max_i = i;
			max_xj = xj;
		}
	}

	for (int d = 0; d < N; d++) {
		int k1 = max_i - d;
		if (d == 0 && xors[k1] == max_xj) {
			ans.first = max_i;
			ans.second = max_i;
			break;
		}
		if (k1 >= 0 && xors[k1] == max_xj) {
			ans.first = k1 + 1;
			ans.second = max_i;
			break;
		}
	}
	best = max_value;
}

int main() {
	ifstream fin("cowxor.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int t;
		fin >> t;
		input.push_back(t);
	}
	trie.push_back(pair<int, int>(-1, -1));
	isXor.push_back(false);

	findXors();
	solve();


	ofstream fout("cowxor.out");
	fout << best << ' ' << ans.first + 1 << ' ' << ans.second + 1 << '\n';
}