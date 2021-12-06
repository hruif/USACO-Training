/*
ID: ruifanl1
TASK: nocows
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

int N, K;
int results[200][100];
vector<int> nums;

int maxTreeSize(int k) {
	if (k < 1) {
		return 0;
	}
	if (k == 1) {
		return 1;
	}
	int count = 1;
	for (int i = 0; i < k; i++) {
		count *= 2;
	}
	return count - 1;
}

void printNum(int x) {
	return;
	if (x > 1000) {
		cout << x << endl;
	}
}

int solve(int n, int k) {
	if (n % 2 == 0) {
		return 0;
	}
	if (n < 2 * k - 1) {
		return 0;
	}
	if (k == 1) {
		return n == 1 ? 1 : 0;
	}
	if (k == 2) {
		if (n == 3) {
			return 1;
		}
		return 0;
	}

	if (results[n][k] >= 0) {
		return results[n][k];
	}
	int total = 0;
	int duplicates = 0;
	for (int left = 2 * (k - 1) - 1; left <= n - 2; left += 2) {
		int right = n - 1 - left;
		int a = 0;
		int c = solve(left, k - 1);
		for (int j = 1; j <= k - 1; j++) {
			int b = solve(right, j);
			if (j == k - 1) {
				duplicates += b * c % 9901;
			}
			a += b;
			printNum(a);
		}
		total += c * a % 9901;
		printNum(total);
	}
	total = total * 2 - duplicates;
	results[n][k] = total % 9901;
	return total % 9901;
}

int main() {
	ifstream fin("nocows.in");
	fin >> N >> K;
	memset(results, -1, sizeof(int) * 200 * 100);

	int total = solve(N, K);
	int ans = total % 9901;
	ofstream fout("nocows.out");
	fout << ans << '\n';
}