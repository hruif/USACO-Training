/*
ID: ruifanl1
TASK: contact
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int A, B, N;
vector<char> sequence;
vector<vector<int>> patterns;

int powerOf2(int a) {
	int val = 1;
	for (int i = 0; i < a; i++) {
		val *= 2;
	}
	return val;
}

int findVal(vector<char>& s) {
	int val = 0, bit = powerOf2(s.size() - 1);
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '1') {
			val += bit;
		}
		bit /= 2;
	}
	return val;
}

void valToBits(vector<char>& b, int val, int len) {
	int a = powerOf2(len - 1);
	while (a > 0) {
		if (val - a >= 0) {
			val -= a;
			b.push_back('1');
		}
		else {
			b.push_back('0');
		}
		a /= 2;
	}
}

void findPattern(int p) {
	int max = B;
	if (p + B >= sequence.size()) {
		max = sequence.size() - p;
	}
	for (int i = A; i <= max; i++) {
		vector<char> s;
		for (int j = 0; j < i; j++) {
			s.push_back(sequence[p + j]);
		}
		int val = findVal(s);
		patterns[i][val]++;
	}
}

void findTop(vector<int>& top) {
	vector<bool> allN(200001, false);
	for (int i = 0; i < N; i++) {
		int topN = 0;
		for (int j = 0; j < patterns.size(); j++) {
			for (int k = 0; k < patterns[j].size(); k++) {
				int f = patterns[j][k];
				if (!allN[f] && f > topN) {
					topN = f;
				}
			}
		}
		top.push_back(topN);
		allN[topN] = true;
	}
}

int main() {
	ifstream fin("contact.in");
	fin >> A >> B >> N;
	char buff = '0';
	while (fin.get(buff)) {
		if (buff == '\n') {
			continue;
		}
		sequence.push_back(buff);
	}
	for (int i = 0; i <= B; i++) {
		vector<int> val(powerOf2(i), 0);
		patterns.push_back(val);
	}

	for (int i = 0; i < sequence.size(); i++) {
		findPattern(i);
	}

	vector<int> top;
	findTop(top);

	ofstream fout("contact.out");
	for (int i = 0; i < top.size(); i++) {
		int num = top[i];
		if (num == 0) {
			break;
		}
		int count = 0;
		fout << num << '\n';
		for (int j = 0; j < patterns.size(); j++) {
			for (int k = 0; k < patterns[j].size(); k++) {
				int f = patterns[j][k];
				if (f == top[i]) {
					vector<char> val;
					valToBits(val, k, j);
					if (count == 6) {
						fout << '\n';
						count = 0;
					}
					if (count > 0) {
						fout << ' ';
					}
					count++;
					for (int l = 0; l < val.size(); l++) {
						fout << val[l];
					}
				}
			}
		}
		fout << '\n';
	}
}