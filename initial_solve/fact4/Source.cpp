/*
ID: ruifanl1
TASK: fact4
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int N;

int multiply(int a, int b) {
	a *= b;
	while (a % 10 == 0) {
		a /= 10;
	}
	a %= 10000;
	return a;
}

int main() {
	ifstream fin("fact4.in");
	fin >> N;

	int ans = 1;
	for (int i = N; i > 0; i--) {
		ans = multiply(ans, i);
	}
	ans %= 10;

	ofstream fout("fact4.out");
	fout << ans << '\n';
}