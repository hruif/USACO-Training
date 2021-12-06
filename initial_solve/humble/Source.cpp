/*
ID: ruifanl1
TASK: humble
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int K, N;
vector<int> humbles, primes;

void sort() {
	for (int i = 0; i < K - 1; i++) {
		for (int j = i + 1; j < K; j++) {
			if (primes[i] > primes[j]) {
				int tmp = primes[i];
				primes[i] = primes[j];
				primes[j] = tmp;
			}
		}
	}
}

int multiply(int a, int b) {
	if (INT_MAX / a < b) {
		return INT_MAX;
	}
	return a * b;
}

int findNext(int n) {
	n++;
	int last = humbles[humbles.size() - 1], nextNum = -1, nextP;
	for (int i = 0; i < K; i++) {
		int p, prime = primes[i + 1];
		bool found = false;
		int p1 = 0;
		int p2 = n;
		while (!found) {
			int mid = (p1 + p2) / 2;
			if (multiply(humbles[mid], prime) <= last) {
				p1 = mid;
				if (p2 - 1 == p1) {
					p = p2;
					found = true;
				}
			}
			else {
				if (p1 == mid) {
					p = mid;
					break;
				}
				p2 = mid;
			}
		}
		if (p == humbles.size()) {
			continue;
		}
		int humbleNum = multiply(humbles[p], prime);
		if (humbleNum < nextNum || nextNum == -1) {
			nextNum = humbleNum;
			if (nextNum - 1 == last) {
				break;
			}
			nextP = p;
		}
		n = p;
	}
	humbles.push_back(nextNum);
	return nextNum;
}

int solve() {
	int ans;
	for (int i = 0; i < N; i++) {
    ans = findNext(i);
	}
	return ans;
}

int main() {
	ifstream fin("humble.in");
	fin >> K >> N;
	primes.push_back(1);
	for (int i = 0; i < K; i++) {
		int tmp;
		fin >> tmp;
		primes.push_back(tmp);
	}
	humbles.push_back(1);

	sort();
	int ans = solve();

	ofstream fout("humble.out");
	fout << ans << '\n';
}