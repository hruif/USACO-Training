/*
ID: ruifanl1
TASK: money
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int V, N;
vector<int> currency;
vector<vector<long long>> results;

long long solve(int n, int lastCoin) {
	if (results[n][lastCoin] >= 0) {
		return results[n][lastCoin];
	}
	long long num = 0;
	for (int i = lastCoin; i >= 0; i--) {
		int next = n - currency[i];
		if (next == 0) {
			num++;
		}
		else if (next > 0) {
			num += solve(next, i);
		}
	}
	results[n][lastCoin] = num;
	return num;
}

int main() {
	ifstream fin("money.in");
	fin >> V >> N;
	for (int i = 0; i < V; i++) {
		int coin;
		fin >> coin;
		currency.push_back(coin);
	}
	for (int i = 0; i <= N; i++) {
		vector<long long> tmp;
		for (int i = 0; i < V; i++) {
			tmp.push_back(-1);
		}
		results.push_back(tmp);
	}

	long long ans = solve(N, V - 1);

	ofstream fout("money.out");
	fout << ans << '\n';
}