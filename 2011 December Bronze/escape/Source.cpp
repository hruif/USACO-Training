#include <iostream>
#include <fstream>

using namespace std;

int n;
int cows[20];
int maxNum;

bool canAdd(int num, int cow) {
	int mod = 1000000000;
	for (int i = 0; i < 9; i++) {
		if (((num % mod) + (cow % mod)) >= mod) {
			return false;
		}
		mod /= 10;
	}
	return true;
}

void findMax(int num, int next, int count) {
	if (next == n) {
		if (count > maxNum) {
			maxNum = count;
		}
		return;
	}
	if (canAdd(num, cows[next])) {
		findMax(num + cows[next], next + 1, count + 1);
	}
	findMax(num, next + 1, count);
}

int main() {
	ifstream fin("escape.in");
	fin >> n;
	for (int i = 0; i < n; i++) {
		fin >> cows[i];
	}
	findMax(0, 0, 0);

	ofstream fout("escape.out");
	fout << maxNum << '\n';
}