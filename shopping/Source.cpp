/*
ID; ruifanl1
TASK: shopping
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

int found[6][6][6][6][6];
vector<int> goal(999, 0), regularP(999), wanted(5), cToIndex(105);
vector<vector<int>> allOffers;

bool isAns(vector<int>& items) {
	for (int i = 0; i < wanted.size(); i++) {
		int item = wanted[i];
		if (goal[item] != items[item]) {
			return false;
		}
	}
	return true;
}

void buyOffer(int index, vector<int>& items, int totalCost) {
	int n = allOffers[index][0];
	for (int i = 1; i <= n; i++) {
		int c = allOffers[index][i * 2 - 1];
		items[c] += allOffers[index][i * 2];
	}
	for (int i = 0; i < wanted.size(); i++) {
		int item = wanted[i];
		if (items[item] > goal[item]) {
			for (int i = 1; i <= n; i++) {
				int c = allOffers[index][i * 2 - 1];
				items[c] -= allOffers[index][i * 2];
			}
			return;
		}
	}
	int foundNum = found[items[wanted[0]]][items[wanted[1]]][items[wanted[2]]][items[wanted[3]]][items[wanted[4]]];
	if (foundNum == -1 || foundNum > totalCost) {
		found[items[wanted[0]]][items[wanted[1]]][items[wanted[2]]][items[wanted[3]]][items[wanted[4]]] = totalCost;
		for (int i = 0; i < allOffers.size(); i++) {
			buyOffer(i, items, allOffers[i][allOffers[i].size() - 1] + totalCost);
		}
	}
	for (int i = 1; i <= n; i++) {
		int c = allOffers[index][i * 2 - 1];
		items[c] -= allOffers[index][i * 2];
	}
	return;
}

void findAns() {
	vector<int> items(999, 0);
	for (int i = 0; i < wanted.size(); i++) {
		items[wanted[i]] = 0;
	}
	for (int i = 0; i < allOffers.size(); i++) {
		buyOffer(i, items, allOffers[i][allOffers[i].size() - 1]);
	}
}

int main() {
	memset(found, -1, sizeof(found));
	ifstream fin("shopping.in");
	int s;
	fin >> s;
	for (int i = 0; i < s; i++) {
		vector<int> offer;
		int n;
		fin >> n;
		offer.push_back(n);
		for (int i = 0; i < n; i++) {
			int c, k;
			fin >> c >> k;
			offer.push_back(c - 1);
			offer.push_back(k);
		}
		int p;
		fin >> p;
		offer.push_back(p);
		allOffers.push_back(offer);
	}
	int b;
	fin >> b;
	for (int i = 0; i < b; i++) {
		vector<int> regular;
		int c, k, p;
		fin >> c >> k >> p;
		regular.push_back(1);
		regular.push_back(c - 1);
		regular.push_back(1);
		regular.push_back(p);
		allOffers.push_back(regular);
		goal[c - 1] = k;
		wanted[i] = c - 1;
		cToIndex[c - 1] = i;
	}

	findAns();
	int ans = found[goal[wanted[0]]][goal[wanted[1]]][goal[wanted[2]]][goal[wanted[3]]][goal[wanted[4]]];
	if (ans == -1) {
		ans = 0;
	}
	ofstream fout("shopping.out");
	fout << ans << '\n';
}