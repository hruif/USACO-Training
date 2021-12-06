/*
ID: ruifanl1
TASK: fracdec
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

int N, D, start = -1, last, differences[1000001];
vector<int> ans;

void divide(int n, int d) {
	while (n != 0) {
		n *= 10;
		if (differences[n] >= 0) {
			start = differences[n];
			break;
		}
		else {
			differences[n] = last;
		}
		ans.push_back(n / d);
		n %= d;
		last++;
	}
	last--;
}

void print() {
	ofstream fout("fracdec.out");
	int whole = N / D, len = 0, tmp = whole;
	if (whole == 0) {
		len = 1;
	}
	while (tmp != 0) {
		len++;
		tmp /= 10;
	}
	fout << whole << '.';
	len++;
	if (start >= 0) {
		for (int i = 0; i < start; i++) {
			fout << ans[i];
			len++;
			if (len == 76) {
				fout << '\n';
				len = 0;
			}
		}
		fout << '(';
		len++;
		if (len == 76) {
			fout << '\n';
			len = 0;
		}
		for (int i = start; i <= last; i++) {
			fout << ans[i];
			len++;
			if (len == 76) {
				fout << '\n';
				len = 0;
			}
		}
		fout << ')';
		len++;
		if (len == 76) {
			fout << '\n';
			len = 0;
		}
	}
	else {
		if (last == -1) {
			fout << 0;
			len++;
			if (len == 76) {
				fout << '\n';
				len = 0;
			}
		}
		for (int i = 0; i <= last; i++) {
			fout << ans[i];
			len++;
			if (len == 76) {
				fout << '\n';
				len = 0;
			}
		}
	}
	fout << '\n';
}

int main() {
	ifstream fin("fracdec.in");
	fin >> N >> D;
	memset(differences, -1, sizeof(differences));
	divide(N % D, D);
	print();
}