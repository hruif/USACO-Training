/*
ID: ruifanl1
TASK: preface
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int N;

int main() {
	ifstream fin("preface.in");
	fin >> N;
	int I, V, X, L, C, D, M;
	I = N / 5 * 7;
	if (N % 5 > 0) {
		I += 1;
		if (N % 5 > 1) {
			I += 2;
			if (N % 5 > 2) {
				I += 3;
				if (N % 5 > 3) {
					I += 1;
				}
			}
		}
	}

	V = N / 10 * 5;
	if (N >= 4) {
		if (N % 10 >= 4) {
			if (N % 10 == 9) {
				V += 5;
			}
			else {
				V += N % 10 - 3;
			}
		}
	}

	X = N / 50 * 70;
	X += N / 10;
	if (N > 10) {
		int r = N % 50;
		int tens = 0;
		if (r >= 10) {
			tens = 1;
			if (r >= 20) {
				tens = 2;
				X += 10;
				if (r >= 30) {
					tens = 3;
					X += 20;
					if (r >= 40) {
						tens = 1; //XL not XXXX
						X += 30;
					}
				}
			}
		}
		r %= 10;
		if (r >= 9) {
			X += 1;
		}
		X += (r + 1) * tens;
	}

	L = N / 100 * 50;
	if (N >= 40) {
		int r = N % 100;
		if (r >= 40) {
			if (r >= 90) {
				L += 50;
			}
			else {
				L += r - 39;
			}
		}
	}

	C = N / 500 * 700; //every 500 has 700 Cs
	C += N / 100 * 10; //every 100 has 10 extra Cs ((n-1)90 - n00)
	if (N > 100) {
		int r = N % 500; //remainder of 500s
		int hundreds = 0;
		if (r >= 100) {
			hundreds = 1; //on Cs in 100s
			if (r >= 200) {
				hundreds = 2; //two Cs in 200s
				C += 100; //for Cs in 100s
				if (r >= 300) {
					hundreds = 3; //three Cs in 300s
					C += 200;
					if (r >= 400) {
						hundreds = 1; //same as with X
						C += 300;
					}
				}
			}
		}
		r %= 100; //remainder of 100s
		if (r >= 90) { //extra Ms if 900 or above
			C += N % 10 + 1;
		}
		C += (r + 1) * hundreds; //how many Cs in current 100
	}
	else if (N >= 90) {
		C += N % 10 + 1;
	}

	D = N / 1000 * 500;
	if (N >= 400) {
		int r = N % 1000;
		if (r >= 400) {
			if (r >= 900) {
				D += 500;
			}
			else {
				D += r - 399;
			}
		}
	}

	M = N / 5000 * 7000; //every 5000 has 7000 Ms
	M += N / 1000 * 100; //every 1000 has 100 extra Ms((n-1)900 - n000)
	if (N > 1000) {
		int r = N % 5000; //remainder of the 5000s
		int thousands;
		if (r >= 1000) {
			thousands = 1; //one M in 1000s
			if (r >= 2000) {
				thousands = 2; //two Ms in 2000s
				M += 1000; //for Ms in 1000s
				if (r >= 3000) {
					thousands = 3;
					M += 2000;
					if (r >= 4000) {
						thousands = 1; //same as with X
						M += 3000;
					}
				}
			}
		}
		r %= 1000; //remainder of 1000s
		if (r >= 900) { //extra Ms if 900 or above
			M += N % 100 + 1;
		}
		M += (r + 1) * thousands; //how many Ms in current 1000
	}
	else if (N >= 900) {
		M += N % 100 + 1;
	}

	ofstream fout("preface.out");
	fout << 'I' << ' ' << I << '\n';
	if (V > 0) {
		fout << 'V' << ' ' << V << '\n';
	}
	if (X > 0) {
		fout << 'X' << ' ' << X << '\n';
	}
	if (L > 0) {
		fout << 'L' << ' ' << L << '\n';
	}
	if (C > 0) {
		fout << 'C' << ' ' << C << '\n';
	}
	if (D > 0) {
		fout << 'D' << ' ' << D << '\n';
	}
	if (M > 0) {
		fout << 'M' << ' ' << M << '\n';
	}
}