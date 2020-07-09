/*
ID: ruifanl1
TASK: job
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, M1, M2, bAns, aAns;
vector<int> A, B;

void solve() {
	vector<int> toIntermediate(N * 20 + 1, 0);
	for (int i = 0; i < A.size(); i++) {
		int processTime = A[i];
		for (int j = 1; j <= N; j++) {
			toIntermediate[processTime * j]++;
		}
	}

	vector<int> fromIntermediate(N * 20 + 1, 0);
	for (int i = 0; i < B.size(); i++) {
		int processTime = B[i];
		for (int j = 1; j <= N; j++) {
			fromIntermediate[processTime * j]++;
		}
	}

	vector<int> ATimes;
	int time = 0;
	for (int i = 0; i < N; i++) {
		while (toIntermediate[time] == 0) {
			time++;
		}
		ATimes.push_back(time);
		toIntermediate[time]--;
	}
	aAns = time;

	vector<int> BTimes;
	time = 0;
	for (int i = 0; i < N; i++) {
		while (fromIntermediate[time] == 0) {
			time++;
		}
		BTimes.push_back(time);
		fromIntermediate[time]--;
	}

	vector<int> allTimes;
	for (int i = 0; i < N; i++) {
		int bVal = ATimes[i] + BTimes[N - i - 1];
		if (bVal > bAns) {
			bAns = bVal;
		}
	}
}

int main() {
	ifstream fin("job.in");
	fin >> N >> M1 >> M2;
	for (int i = 0; i < M1; i++) {
		int tmp;
		fin >> tmp;
		A.push_back(tmp);
	}
	for (int i = 0; i < M2; i++) {
		int tmp;
		fin >> tmp;
		B.push_back(tmp);
	}

	solve();

	ofstream fout("job.out");
	fout << aAns << ' ' << bAns << '\n';
}