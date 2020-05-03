/*
ID: ruifanl1
TASK: subset
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

int N, half, ans;
int results[40][400];
int totalCalls;
vector<int> nums;

void printNums() {
	return;
	for (int i = 0; i < nums.size(); i++) {
		cout << nums[i] << ' ';
	}
	cout << endl;
}

int subset(int n, int sum) {
	if (sum == 0) {
		printNums();
		return 1;
	}
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		if (sum == 1) {
			nums.push_back(1);
			printNums();
			nums.pop_back();
			return 1;
		}
		return 0;
	}
	if (n == 2) {
		if (sum >= 1 && sum <= 3) {
			if (sum <= 2) {
				nums.push_back(sum);
			}
			else {
				nums.push_back(3);
			}
			printNums();
			nums.pop_back();
			return 1;
		}
		return 0;
	}
	totalCalls++;
	if (results[n - 1][sum - 1] >= 0) {
		return results[n - 1][sum - 1];
	}
	int count = 0;
	for (int i = n; i >= 1; i--) {
		if (sum - i >= 0) {
			nums.push_back(i);
			count += subset(i - 1, sum - i);
			nums.pop_back();
		}
	}
	results[n - 1][sum - 1] = count;
	return count;
}

int main() {
	ifstream fin("subset.in");
	fin >> N;

	memset(results, -1, 4 * 40 * 400);
	half = (N + 1) * N / 4;
	if (N*(N + 1) / 2 % 2 == 1) {
		ans = 0;
	}
	else {
		ans = subset(N - 1, half - N);
	}
	ofstream fout("subset.out");
	fout << ans << '\n';
}