/*
ID: ruifanl1
TASK: zerosum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N;
vector<int> operators;
vector<vector<int>> results;
ofstream fout("zerosum.out");

void printSol() {
	for (int i = 1; i <= N; i++) {
		if (operators[i] == 0) {
			fout << ' ';
		}
		if (operators[i] == 1) {
			fout << '+';
		}
		if (operators[i] == 2) {
			fout << '-';
		}
		fout << i;
	}
	fout << '\n';
}

bool checkSol() {
	int num = 0;
	for (int i = 1; i <= N; i++) {
		int toAdd = i;
		int op = operators[i];
		while (i < N && operators[i + 1] == 0) {
			i++;
			toAdd *= 10;
			toAdd += i;
		}
		if (op == 2) {
			while (i < N && operators[i + 1] == 0) {
				i++;
				toAdd *= 10;
				toAdd += i;
			}
			toAdd = -toAdd;
		}
		num += toAdd;
	}
	if (num == 0) {
		return true;
	}
	return false;
}

void solve(int digit, int op) {
	operators[digit] = op;
	if (digit == N) {
		if (checkSol()) {
			printSol();
		}
		return;
	}
	int next = digit + 1;
	for (int i = 0; i <= 2; i++) {
		solve(next, i);
	}
}

int main() {
	ifstream fin("zerosum.in");
	fin >> N;
	for (int i = 0; i <= N; i++) {
		operators.push_back(-1);
	}
	results.resize(3);

	for (int i = 0; i < 3; i++) {
		solve(2, i);
	}
}