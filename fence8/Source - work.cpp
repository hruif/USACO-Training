/*
ID: ruifanl1
TASK: fence8
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, R, total, leftover, mid;
vector<int> boards;
vector<int> rails;
vector<int> sum;

void sortRails() {
	for (int i = 1; i < rails.size() - 1; i++) {
		for (int j = i + 1; j < rails.size(); j++) {
			if (rails[i] > rails[j]) {
				int t = rails[i];
				rails[i] = rails[j];
				rails[j] = t;
			}
		}
	}
}

bool cutRail(int start, int m) {
	if (m == 0) {
		return true;
	}
	if (leftover > total - sum[mid]) {
		return false;
	}
	int size = rails[m];
	for (int i = start; i < boards.size(); i++) {
		if (boards[i] < size) {
			continue;
		}
		boards[i] -= size;
		if (boards[i] < rails[1]) {
			leftover += boards[i];
		}
		int next = m - 1;

		bool found;
		if (rails[next] == rails[m]) {
			found = cutRail(i, next);
		}
		else {
			found = cutRail(1, next);
		}
		if (boards[i] < rails[1]) {
			leftover -= boards[i];
		}
		boards[i] += size;
		if (found) {
			return true;
		}
	}
	return false;
}

int findMaxRail() {
	int totalB = 0;
	for (int i = 1; i < boards.size(); i++) {
		totalB += boards[i];
	}
	int totalR = 0;
	int max = rails.size() - 1;
	for (int i = 1; i < rails.size(); i++) {
		totalR += rails[i];
		if (totalR >= totalB) {
			if (totalR > totalB) {
				i--;
			}
			max = i;
			break;
		}
	}
	return max;
}

int main() {
	ifstream fin("fence8.in");
	fin >> N;
	boards.push_back(-1);
	for (int i = 0; i < N; i++) {
		int t;
		fin >> t;
		boards.push_back(t);
		total += t;
	}
	fin >> R;
	sum.resize(R + 1);
	sum[0] = 0;
	rails.push_back(-1);
	for (int i = 0; i < R; i++) {
		int t;
		fin >> t;
		rails.push_back(t);
	}

	vector<bool> cut(R, false);

	sortRails();
	for (int i = 1; i < rails.size(); i++) {
		sum[i] = sum[i - 1] + rails[i];
	}

	int l = 1;
	int r = findMaxRail();
	int ans = 0;
	while (l <= r) {
		mid = (l + r) / 2;
		if (cutRail(1, mid)) {
			ans = mid;
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}

	ofstream fout("fence8.out");
	fout << ans << '\n';
}