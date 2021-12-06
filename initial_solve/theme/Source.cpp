/*
ID: ruifanl1
TASK: theme
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N;
vector<int> notes;
vector<int> values;

void findValues() {
	values.resize(N);
	values[0] = -1;
	for (int i = 1; i < N; i++) {
		values[i] = notes[i] - notes[i - 1];
	}
}

int main() {
	ifstream fin("theme.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		fin >> tmp;
		notes.push_back(tmp);
	}

	findValues();

	int ans = 0;

	for (int i = 0; i <= N - 10; i++) {
		if (ans * 2 >= N - i) {
			break;
		}
		for (int j = i + 5; j < N; j++) {
			if (ans >= N - j) {
				break;
			}
			bool end = false; // if found to end, no need to search more for j
			int p1 = i; // position of first sequence;
			int p2 = j; // position of second sequence;
			int len = 0;

			while (true) {
				if (p2 == N) {
					end = true;
					break;
				}
				if (p1 >= j) {
					break;
				}
				if (values[p1] == values[p2] || p1 == i) {
					len++;
					p1++;
					p2++;
					if (len > ans) {
						ans = len;
					}
				}
				else {
					break;
				}
			}
			if (end) {
				break;
			}
		}
	}

	ofstream fout("theme.out");
	if (ans >= 5) {
		fout << ans;
	}
	else {
		fout << 0;
	}
	fout << '\n';
}