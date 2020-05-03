/*
ID: ruifanl1
TASK: runround
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

bool isRunround(unsigned long n) {
	char s[10];
	bool flags[10];
	memset(flags, 0, sizeof(bool) * 10);
	sprintf(s, "%lu", n);
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		char c = s[i] - '0';
		if (c == 0) {
			return false;
		}
		if (flags[c]) {
			return false;
		}
		flags[c] = true;
	}
	int i = 0;
	int count = 0;
	while (true) {
		char c = s[i] - '0';
		if (!flags[c]) {
			return false;
		}
		count++;
		i = (i + c) % len;
		if (count == len) {
			return i == 0;
		}
		flags[c] = false;
		
	}
}

unsigned long runround(unsigned long n) {
	for (int i = n + 1; ; i++) {
		if (isRunround(i)) {
			return i;
		}
	}
}

int main() {
	ifstream fin("runround.in");
	unsigned long n;
	fin >> n;

	int result = runround(n);
	ofstream fout("runround.out");
	fout << result << '\n';
}