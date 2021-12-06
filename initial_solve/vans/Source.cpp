/*
ID: ruifanl1
TASK: vans
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> ans;
vector<int> allRoutes[6];

void bigAdd(vector<int> a, vector<int> b, vector<int>& c) {
	int carry = 0;
	int aLen = a.size();
	int bLen = b.size();
	int len = max(aLen, bLen);
	c.resize(len);
	for (int i = 0; i < len; i++) {
		c[i] = carry;
		if (i < aLen) {
			c[i] += a[i];
		}
		if (i < bLen) {
			c[i] += b[i];
		}
		carry = c[i] / 10;
		c[i] %= 10;
	}
	if (carry != 0) {
		c.push_back(carry);
	}
}

void findRoutes() {
	vector<int> newRoutes[6];
	newRoutes[0] = allRoutes[1];
	bigAdd(newRoutes[0], allRoutes[2], newRoutes[0]);
	bigAdd(newRoutes[0], allRoutes[3], newRoutes[0]);
	bigAdd(newRoutes[0], allRoutes[4], newRoutes[0]);

	newRoutes[1] = allRoutes[1];
	bigAdd(newRoutes[1], allRoutes[3], newRoutes[1]);
	bigAdd(newRoutes[1], allRoutes[4], newRoutes[1]);

	newRoutes[2] = allRoutes[0];

	newRoutes[3] = allRoutes[0];
	bigAdd(newRoutes[3], allRoutes[5], newRoutes[3]);

	newRoutes[4] = allRoutes[0];
	bigAdd(newRoutes[4], allRoutes[5], newRoutes[4]);

	newRoutes[5] = allRoutes[0];
	bigAdd(newRoutes[5], allRoutes[5], newRoutes[5]);

	allRoutes[0] = newRoutes[0];
	allRoutes[1] = newRoutes[1];
	allRoutes[2] = newRoutes[2];
	allRoutes[3] = newRoutes[3];
	allRoutes[4] = newRoutes[4];
	allRoutes[5] = newRoutes[5];
}

int main() {
	ifstream fin("vans.in");
	fin >> N;
	if (N <= 3) { // algorithm requires at least N == 4
		if (N == 1) {
			ans.push_back(0);
		}
		else if (N == 2) {
			ans.push_back(2);
		}
		else if (N == 3) {
			ans.push_back(4);
		}
	}
	else {
		allRoutes[0].push_back(1);
		allRoutes[1].push_back(1);
		for (int i = 3; i < N; i++) {
			findRoutes();
		}
		bigAdd(allRoutes[0], allRoutes[1], ans);
		bigAdd(ans, allRoutes[2], ans);
		bigAdd(ans, allRoutes[3], ans);
		bigAdd(ans, allRoutes[4], ans);
		bigAdd(ans, allRoutes[5], ans);
		bigAdd(ans, ans, ans);
	}

	ofstream fout("vans.out");
	for (int i = ans.size() - 1; i >= 0; i--) {
		fout << ans[i];
	}
	fout << '\n';
}