/*
ID: ruifanl1
TASK: sprime
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

vector<int> primes, ans;

char num[10];

int N, totalAns;

bool checkPrime(int val)
{
	if (val < 2) {
		return false;
	}
	int a = sqrt(val);
	for (int i = 0; i < primes.size(); i++) {
		if (a < primes[i]) {
			return true;
		}
		if (val % primes[i] == 0) {
			return false;
		}
	}
	return true;
}

void findPrimes(int maxVal)
{
	primes.push_back(2);
	int maxPrime = sqrt(maxVal);
	int lastPrime = 3;
	for (int i = 3; i <= maxPrime; i += 2) {
		if (checkPrime(i)) {
			primes.push_back(i);
		}
	}
}

int setMaxVal()
{
	char buff[10];
	for (int i = 0; i < N; i++) {
		buff[i] = '9';
	}
	buff[N] = 0;
	return atoi(buff);
}

void addRibs(int digitsAdded)
{
	for (int i = 0; i < 10; i++) {
		if (digitsAdded == N - 1 && i % 2 == 0) {
			continue;
		}
		num[digitsAdded] = i + '0';
		num[digitsAdded + 1] = 0;
		int tmpNum = atoi(num);
		if (checkPrime(tmpNum)) {
			if (digitsAdded + 1 == N) {
				ans.push_back(tmpNum);
				totalAns++;
			}
			else {
				addRibs(digitsAdded + 1);
			}
		}
	}
	num[digitsAdded] = 0;
	return;
}

int main()
{
	ifstream fin("sprime.in");
	ofstream fout("sprime.out");
	fin >> N;
	int maxVal = setMaxVal();
	findPrimes(maxVal);
	addRibs(0);
	for (int i = 0; i < totalAns; i++) {
		fout << ans[i] << '\n';
	}
}