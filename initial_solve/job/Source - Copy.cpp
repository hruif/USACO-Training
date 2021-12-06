/*
ID: ruifanl1
TASK: job
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M1, M2, BAns = -1;
vector<int> A, B;
vector<int> intermediateTimes, outputTimes;
vector<int> found;

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

void findOutput(int last, int onStart, vector<int>& canStarts, vector<vector<int>>& BStarts) {
	if (last != -1) {
		if (onStart != 0) {
			if (canStarts[onStart] > BStarts[last].back()) {
				BStarts[last][BStarts[last].size() - 1] = canStarts[onStart];
			}
		}
		if (onStart == N) {
			int time = -1;
			for (int i = 0; i < BStarts.size(); i++) {
				if (BStarts[i].size() == 0) {
					continue;
				}
				if (BStarts[i].back() > time) {
					time = BStarts[i].back();
				}
			}
			if (BAns > time || BAns == -1) {
				BAns = time;
			}
			return;
		}
	}

	for (int i = 0; i < B.size(); i++) {
		if (BStarts[i].size() == 0) {
			BStarts[i].push_back(B[i] + canStarts[0]);
		}
		else {
			BStarts[i].push_back(BStarts[i].back() + B[i]);
		}
		findOutput(i, onStart + 1, canStarts, BStarts);
		BStarts[i].pop_back();
	}
}

int solveB(vector<int>& timeStarts, vector<int>& allTs) {
	int time = 0;
	vector<int> queueTimes(M2, 0);
	for (int i = 0; i < N - M2; i++) {
		while (timeStarts[time] == 0) {
			for (int j = 0; j < M2; j++) {
				queueTimes[j]--;
			}
			time++;
		}
		int least = -1;
		int bestB;
		for (int j = 0; j < M2; j++) {
			if (queueTimes[j] + B[j] < least || least == -1) {
				least = queueTimes[j] + B[j];
				bestB = j;
			}
		}
		queueTimes[bestB] = least;
		allTs[bestB] = least + time;
		timeStarts[time]--;
	}
	for (int i = 0; i < M2; i++)
	{
		queueTimes[i] += time;
	}
	int ans = -1;
	for (int i = 0; i < M2; i++) {
		if (queueTimes[i] > ans) {
			ans = queueTimes[i];
		}
	}
	ans += time;
	return ans;
}

int f(int jobs, vector<int>& allTs, vector<int>& startTimes) {
	if (jobs == 0) {
		int high = -1;
		for (int i = 0; i < allTs.size(); i++) {
			if (allTs[i] > high) {
				high = allTs[i];
			}
		}
		return high;
	}
	
	int best = -1;
	for (int i = 0; i < M2; i++) {
		int old = allTs[i];
		allTs[i] = max(allTs[i], startTimes[N - jobs]) + B[i];
		int time = f(jobs - 1, allTs, startTimes);
		if (time < best || best == -1) {
			best = time;
		}
		allTs[i] = old;
	}
	return best;
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

	vector<int> canStarts, timeStarts(N * 20 + index + 1, 0);
	for (int i = 0; i < N; i++) {
		while (processed[index] == 0) {
			index++;
		}
		intermediateTimes.push_back(index);
		canStarts.push_back(index);
		timeStarts[index]++;
		processed[index]--;
	}
	processed.clear();
	processed.resize(N * 20 + index + 1, 0);
	int overlap = 0;
	vector<int> starts(N * 20 + index + 1, 0);
	vector<vector<int>> BStarts(B.size());
	found.resize(N * 20 + index + 1, -1);
	vector<int> allTs(M2, 0);
	findOutput(-1, 0, canStarts, BStarts);
	int a = 0;
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
	fout << intermediateTimes.back() << ' ' << BAns << '\n';
}