/*
ID: ruifanl1
TASK: fence9
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

double n, m, p;
int og[2], lat[2], latx[2];
double lSlope;
double rSlope;

int findLats(int y) {
	double min = lSlope * y;
	double max =  p - rSlope * y;
	int intMin = min;
	int intMax = max;
	int val = intMax - intMin;
	if (double(intMax) == max) {
		val--;
	}
	if (intMin == intMax) {
		val = 0;
	}
	return val;
}

int main() {
	ifstream fin("fence9.in");
	fin >> n >> m >> p;
	lat[0] = n;
	lat[1] = m;
	latx[0] = p;

	int ans = 0;
	if (m != 0) {
		lSlope = n / m;
		rSlope = (p - n) / m;


		for (int i = 1; i < m; i++) {
			ans += findLats(i);
		}
	}
	ofstream fout("fence9.out");
	fout << ans << '\n';
}