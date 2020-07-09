/*
ID: ruifanl1
TASK: job
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, M1, M2;
vector<int> A, B;
vector<int> intermediateTimes, outputTimes;

void order() {
	for (int i = 0; i < B.size() - 1; i++) {
		for (int j = i + 1; j < B.size(); j++) {
			if (B[i] < B[j]) {
				int tmp = B[i];
				B[i] = B[j];
				B[j] = tmp;
			}
		}
	}
}

void findOutput(int time, vector<int>& canStarts) {

}

void findAns() {
	vector<int> processed(N * 20 + 1, 0);
	for (int i = 0; i < A.size(); i++) {
		int time = 1;
		int timeNeeded = A[i];
		int numProcessed;
		while (true) {
			numProcessed = time / timeNeeded;
			if (time % timeNeeded == 0) {
				processed[time]++;
			}
			if (numProcessed == N) {
				break;
			}
			time++;
		}
	}
	int index = 0;

	vector<int> canStarts;
	for (int i = 0; i < N; i++) {
		while (processed[index] == 0) {
			index++;
		}
		intermediateTimes.push_back(index);
		canStarts.push_back(index);
		processed[index]--;
	}
	processed.clear();
	processed.resize(N * 20 + index + 1, 0);
	int overlap = 0;
	vector<int> starts(N * 20 + index + 1, 0);
	for (int i = 0; i < B.size(); i++) {
		int time = 1;
		int timeNeeded = B[i];
		int lastTime = 0;
		int numProcessed = 0;
		while (true) {
			int recorded = intermediateTimes[numProcessed];
			bool overlapped = false;

			if (recorded <= lastTime) {
				recorded = lastTime;
			}
			else {
				overlap++;
				overlapped = true;
			}
			if (time - recorded >= timeNeeded) {
				if (numProcessed == 0) {
					if (canStarts[time - timeNeeded] != 0 && starts[time - timeNeeded] >= canStarts[time - timeNeeded]) {
						time++;
						continue;
					}
					else {
						starts[time - timeNeeded]++;
					}
				}
				processed[time]++;
				lastTime = time;
				numProcessed++;
			}
			else {
				if (overlapped) {
					overlap--;
				}
			}
			if (numProcessed == N) {
				break;
			}
			time++;
		}
	}
	for (int i = 0; i < N; i++) {
		int index = 0;
		while (processed[index] == 0) {
			index++;
		}
		outputTimes.push_back(index);
		processed[index]--;
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

	order();
	findAns();

	ofstream fout("job.out");
	fout << intermediateTimes.back() << ' ' << outputTimes.back() << '\n';
}