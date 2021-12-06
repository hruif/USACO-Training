/*
ID: ruifanl1
TASK: concom
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n;
vector<bool> owned;
vector<vector<int>> companies;
vector<vector<bool>> controlled;

void find(int company, vector<int>& controlling) {
	if (owned[company]) {
		return;
	}
	for (int i = 0; i < controlling.size(); i++) {
		if (!controlled[controlling[i]][company]) {
			controlled[controlling[i]][company] = true;
			companies[i].push_back(company);
		}
	}
	controlling.push_back(company);
	owned[company] = true;
	for (int i = 0; i < companies[company].size(); i++) {
		find(companies[company][i], controlling);
	}
	owned[company] = false;
	controlling.pop_back();
}

int main() {
	ifstream fin("concom.in");
	fin >> n;
	for (int l = 0; l < n; l++) {
		int i, j, p;
		vector<int> vals;
		fin >> i >> j >> p;
		while (i >= companies.size()) {
			vector<int> tmp;
			companies.push_back(tmp);
		}
		if (p > 50) {
			companies[i].push_back(j);
		}
	}

	owned.resize(companies.size(), false);
	for (int i = 0; i < companies.size(); i++) {
		vector<bool> tmp(companies.size(), false);
		controlled.push_back(tmp);
	}
	for (int i = 0; i < companies.size(); i++) {
		for (int j = 0; j < companies[i].size(); j++) {
			controlled[i][companies[i][j]] = true;
		}
	}

	vector<int> controlling;
	find(1, controlling);

	for (int i = 0; i < companies.size(); i++) {
		for (int j = 0; j < companies[i].size() - 1; j++) {
			for (int k = j + 1; k < companies[i].size(); k++) {
				if (companies[i][j] > companies[i][k]) {
					int tmp = companies[i][j];
					companies[i][j] = companies[i][k];
					companies[i][k] = tmp;
				}
			}
		}
	}

	ofstream fout("concom.out");
	for (int i = 1; i < companies.size(); i++) {
		for (int j = 0; j < companies[i].size(); j++) {
			int owned = companies[i][j];
			if (owned != i) {
				fout << i << ' ' << owned << '\n';
			}
		}
	}
}