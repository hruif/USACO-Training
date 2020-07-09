/*
ID: ruifanl1
TASK: buylow
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N, numOf;
vector<int> prices;
vector<short> found, starts, whatNum, answer;
vector<vector<short>> canBuy, pathStarts, fullPaths, sameP, pathFound;

void addTo(vector<short> a, vector<short>& b, vector<short>& c) {
	int bSize = b.size();
	int aSize = a.size();
	int maxSize = max(aSize, bSize);
	a.resize(maxSize, 0);
	b.resize(maxSize, 0);
	c.resize(maxSize + 1, 0);
	int carry = 0;
	for (int i = 0; i < maxSize; i++) {
		c[i] = a[i] + b[i] + carry;
		carry = c[i] / 10;
		c[i] %= 10;
	}
	if (carry != 0) {
		c[maxSize] = carry;
	}
	else {
		c.pop_back();
	}
}

bool isDupe(vector<short>& a, int price) {
	int len = a.size();
	for (int i = 0; i < len; i++) {
		if (prices[a[i]] == price) {
			return true;
		}
	}
	return false;
}

void findPaths() {
	canBuy.resize(N);
	for (int i = 0; i < N - 1; i++) {
		int max = 0;
		vector<bool> flags(N, false);
		for (int j = i + 1; j < N; j++) {
			if (prices[i] <= prices[j] || prices[j] < max) {
				continue;
			}
			if (flags[j]) {
				continue;
			}
			// flag duplicates
			for (int k = 0; k < sameP[j].size(); k++) {
				flags[sameP[j][k]] = true;
			}
			if (prices[j] > max) {
				max = prices[j];
			}
			canBuy[i].push_back(j);
		}
	}
}

int buyStock(int start) {
	if (start == N - 1) {
		found[start] = 1;
		return 1;
	}
	if (found[start] != -1) {
		return found[start];
	}
	int maxLen = 0;
	vector<short> maxLenSequences;
	int len = canBuy[start].size();
	if (len == 0) {
		found[start] = 1;
		return 1;
	}
	vector<bool> bought(N, false);
	for (int i = 0; i < len; i++) {
		int next = canBuy[start][i];
		if (prices[next] >= prices[start]) {
			continue;
		}
		int len = buyStock(canBuy[start][i]);
		if (len == maxLen) {
			maxLenSequences.push_back(next);
		}
		if (len > maxLen) {
			maxLen = len;
			maxLenSequences.clear();
			maxLenSequences.push_back(next);
		}
	}
	pathStarts[start] = maxLenSequences;
	found[start] = maxLen + 1;
	return maxLen + 1;
}

int findMaxLen() {
	int maxLen = 0;
	vector<bool> flags(N, false);
	for (int i = 0; i < N; i++) {
		if (flags[i]) {
			continue;
		}
		int len = buyStock(i);
		if (len == maxLen) {
			starts.push_back(i);
		}
		if (len > maxLen) {
			starts.clear();
			starts.push_back(i);
			maxLen = len;
		}
		for (int j = 0; j < sameP[i].size(); j++) {
			flags[sameP[i][j]] = true;
		}
	}
	return maxLen;
}

void numToB(int num, vector<short>& b) {
	int carry = num;
	while (carry != 0) {
		int digit = carry % 10;
		b.push_back(digit);
		carry /= 10;
	}
}

void findNextInPath(int last, vector<short>& ans) {
	int len = pathStarts[last].size();
	vector<short>& a = pathFound[last];
	if (a.size() > 0) {
		addTo(ans, a, ans);
		return;
	}
	if (len == 0) {
		numToB(1, a);
		addTo(ans, a, ans);
		pathFound[last] = a;
		return;
	}
	for (int i = 0; i < pathStarts[last].size(); i++) {
		int next = pathStarts[last][i];
		findNextInPath(next, ans);
		addTo(a, pathFound[next], a);
	}
	pathFound[last] = a;
	return;
}

void findFullPaths(int max) {
	for (int i = 0; i < starts.size(); i++) {
		findNextInPath(starts[i], answer);
	}
}

void findSame() {
	for (int i = 0; i < prices.size() - 1; i++) {
		for (int j = i + 1; j < prices.size(); j++) {
			if (prices[j] == prices[i]) {
				sameP[i].push_back(j);
			}
		}
	}
}

int main() {
	ifstream fin("buylow.in");
	fin >> N;
	found.resize(N, -1);
	pathFound.resize(N);
	pathStarts.resize(N);
	sameP.resize(N);
	for (int i = 0; i < N; i++) {
		int tmp;
		fin >> tmp;
		prices.push_back(tmp);
	}
	int maxLen;

	if (N == 0) {
		maxLen = 0;
	}
	else if (N == 1) {
		maxLen = 1;
		answer.push_back(1);
	}
	else {
		findSame();
		findPaths();
		maxLen = findMaxLen();
		findFullPaths(maxLen);
	}

	ofstream fout("buylow.out");
	fout << maxLen << ' ';
	for (int i = answer.size() - 1; i >= 0; i--) {
		fout << answer[i];
	}
	fout << '\n';
}