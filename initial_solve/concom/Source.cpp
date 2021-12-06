/*
ID: ruifanl1
TASK: concom
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int C;
vector<bool> owned;
vector<int> companies;
vector<vector<int>> shares;
vector<vector<vector<int>>> controlled;

void solve(int a) {
	vector<vector<int>> tmp;
	controlled.push_back(tmp);
	vector<vector<int>>& A = controlled.back();
	for (int i = 0; i <= C; i++) {
		vector<int> tmp;
		if (i == 0) {
			A.push_back(tmp);
			A[i].push_back(a);
			continue;
		}
		int newCount = 0;
		for (int k = 0; k < C; k++) {
			vector<int> A1 = A[i - 1];
			if (find(A1.begin(), A1.end(), companies[k]) != A1.end()) {
				tmp.push_back(companies[k]);
				continue;
			}
			int sum = 0;
			for (int j = 0; j < A1.size(); j++) {
				if (!shares[A1[j]].empty()) {
					sum += shares[A1[j]][companies[k]];
				}
			}
			if (sum > 50) {
				newCount++;
				tmp.push_back(companies[k]);
			}
		}
		if (newCount == 0) {
			return;
		}
		A.push_back(tmp);
	}
}

int main() {
	ifstream fin("concom.in");
	int n;
	fin >> n;
	shares.resize(100);
	C = 0;
	for (int l = 0; l < n; l++) {
		int i, j, p;
		fin >> i >> j >> p;
		if (shares[i - 1].empty()) {
			shares[i - 1].resize(100, 0);
			if (find(companies.begin(), companies.end(), i - 1) == companies.end()) {
				C++;
				companies.push_back(i - 1);
			}
		}
		if (find(companies.begin(), companies.end(), j - 1) == companies.end()) {
			C++;
			companies.push_back(j - 1);
		}

		shares[i - 1][j - 1] = p;
	}
	for (int i = 0; i < companies.size() - 1; i++) {
		for (int j = i + 1; j < companies.size(); j++) {
			if (companies[i] > companies[j]) {
				int tmp = companies[i];
				companies[i] = companies[j];
				companies[j] = tmp;
			}
		}
	}

	for (int i = 0; i < C; i++) {
		solve(companies[i]);
	}

	for (int i = 0; i < controlled.size(); i++) {
		int last = controlled[i].size() - 1;
		for (int j = 0; j < controlled[i][last].size() - 1; j++) {
			for (int k = j + 1; k < controlled[i][last].size(); k++) {
				if (controlled[i][last][j] > controlled[i][last][k]) {
					int tmp = controlled[i][last][j];
					controlled[i][last][j] = controlled[i][last][k];
					controlled[i][last][k] = tmp;
				}
			}
		}
	}
	ofstream fout("concom.out");
	for (int i = 0; i < controlled.size(); i++) {
		for (int j = 0; j < controlled[i].back().size(); j++) {
			int owned = controlled[i][controlled[i].size() - 1][j];
			if (owned != companies[i]) {
				fout << companies[i] + 1 << ' ' << owned + 1 << '\n';
			}
		}
	}
}