/*
ID: ruifanl1
TASK: frac1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int N;
vector<int> primes;

struct Fraction {
	int num;
	int den;
};

void findPrimes(int maxNum) {
	primes.push_back(2);
	for (int i = 3; i <= maxNum; i += 2) {
		int maxPrime = sqrt(i);
		for (int j = 0; j < primes.size(); j++) {
			if (primes[j] > maxPrime) {
				primes.push_back(i);
				break;
			}
			if (i % primes[j] == 0) {
				break;
			}
		}
	}
}

bool isDupe(Fraction& frac) {
	for (int i = 0; i < primes.size(); i++) {
		if (frac.num % primes[i] == 0 && frac.den % primes[i] == 0) {
			return true;
		}
	}
	return false;
}

int main() {
	ifstream fin("frac1.in");
	fin >> N;
	vector<Fraction> fracs;

	Fraction a;
	a.num = 0;
	a.den = 1;
	fracs.push_back(a);
	findPrimes(N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j < i; j++) {
			Fraction frac;
			frac.num = j;
			frac.den = i;
			if (!isDupe(frac)) {
				fracs.push_back(frac);
			}
		}
	}

	for (int i = 0; i < fracs.size() - 1; i++) {
		for (int j = i + 1; j < fracs.size(); j++) {
			if (fracs[i].num * fracs[j].den > fracs[j].num * fracs[i].den) {
				Fraction tmp = fracs[i];
				fracs[i] = fracs[j];
				fracs[j] = tmp;
			}
		}
	}

	a.num = 1;
	a.den = 1;
	fracs.push_back(a);
	ofstream fout("frac1.out");
	for (int i = 0; i < fracs.size(); i++) {
		fout << fracs[i].num << '/' << fracs[i].den << '\n';
	}
}