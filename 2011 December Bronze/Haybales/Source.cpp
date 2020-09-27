#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

int n;
int bales[10000];

int main() {
	ifstream fin("haybales.in");
	fin >> n;
	int total = 0;
	for (int i = 0; i < n; i++) {
		fin >> bales[i];
		total += bales[i];
	}
	int avg = total / n;
	int dist = 0;
	for (int i = 0; i < n; i++) {
		dist += abs(avg - bales[i]);
	}
	ofstream fout("haybales.out");
	fout << dist / 2 << '\n';
}