/*
ID: ruifanl1
TASK: milk4
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int Q, P;
vector<int> pails;

void sortPails() {
	for (int i = 0; i < pails.size() - 1; i++) {
		for (int j = i + 1; j < pails.size(); j++) {
			if (pails[i] > pails[j]) {
				int tmp = pails[i];
				pails[i] = pails[j];
				pails[j] = tmp;
			}
		}
	}
}

bool usePail(int val, vector<int>& usedPails, vector<bool>& visited) {
	if (visited[val]) {
		return false;
	}
	if (val <= 0) {
		if (val == 0) {
			return true;
		}
		else {
			visited[val] = true;
			return false;
		}
	}
	for (int i = usedPails.size() - 1; i >= 0; i--) {
		int nextVal = val - pails[usedPails[i]];
		if (nextVal < 0) {
			break;
		}
		for (int j = 0; j < usedPails.size(); j++) {
			if (nextVal % pails[usedPails[j]] == 0) {
				return true;
			}
		}
		if (usePail(nextVal, usedPails, visited)) {
			return true;
		}
	}
	visited[val] = true;
	return false;
}

bool choosePails(int lastPail, int pailNum, vector<int>& usedPails) {
	if (pailNum == P) {
		vector<bool> visited(Q + 1, false);
		if (usePail(Q, usedPails, visited)) {
			return true;
		}
		else {
			return false;
		}
	}
	int len = pails.size();
	for (int i = lastPail + 1; i < len; i++) {
		if (i == -1) {
			if (choosePails(-2, pailNum + 1, usedPails)) {
				return true;
			}
		}
		else {
			usedPails.push_back(i);
			if (choosePails(i, pailNum + 1, usedPails)) {
				return true;
			}
			usedPails.pop_back();
		}
	}
	return false;
}

int main() {
	ifstream fin("milk4.in");
	fin >> Q >> P;
	for (int i = 0; i < P; i++) {
		int tmp;
		fin >> tmp;
		pails.push_back(tmp);
	}
	sortPails();

	vector<int> usedPails;
	choosePails(-2, 0, usedPails);

	ofstream fout("milk4.out");
	fout << usedPails.size();
	for (int i = 0; i < usedPails.size(); i++) {
		fout << ' ' << pails[usedPails[i]];
	}
	fout << '\n';
}