/*
ID: ruifanl1
TASK: kimbits
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, L, ansN;
unsigned int I;
vector<int> bits;
vector<bool> ans;

int findI(int n, int l) {
	if (l == 0) {
		ansN += bits[n + 1];
		return 1;
	}
	int i;
	if (n > 0) {
		i = findI(n - 1, l);
		if (i < I) {
			ans[n - 1] = true;
			i += findI(n - 1, l - 1);
		}
		else {
			ans[n - 1] = false;
		}
		return i;
	}
	else {
		ansN += 1;
		return 1;
	}
}

bool inS(int num, int usedL) {
	int l = 0;
	for (int i = 0; i < bits.size(); i++) {
		if (num & bits[i]) {
			l++;
		}
	}
	return l <= usedL;
}

int main() {
	ifstream fin("kimbits.in");
	fin >> N >> L >> I;
	int b = 1;
	for (int i = 0; i <= N; i++) {
		bits.push_back(b);
		b *= 2;
	}
	ans.resize(N, false);
	int i =	findI(N, L);

	ansN--;
	ofstream fout("kimbits.out");
	for (int i = bits.size() - 2; i >= 0; i--) {
		if (ansN & bits[i]) {
			fout << 1;
		}
		else {
			fout << 0;
		}
	}
	fout << '\n';
}