/*
ID: ruifanl1
TASK: pprime
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int a, b;
vector<int> allPalindromes, primes, pprimes;

int findLength(int val)
{
	char buf[20];
	sprintf(buf, "%d", val);
	int len = strlen(buf);
	return len;
}

void formPalindrome(char* half, int halfLen, int length) {
	char palindrome[20];
	for (int i = 0; i < halfLen; i++) {
		palindrome[i] = half[i];
		palindrome[length - i - 1] = half[i];
	}
	palindrome[length] = 0;
	int num = atoi(palindrome);
	if (num >= a && num <= b) {
		allPalindromes.push_back(num);
	}
}

void addAndMake(char* num, int toAdd, int halfLen, int length)
{
	toAdd--;
	for (int i = 0; i < 10; i++) {
		if (toAdd == 0 && i == 0) {
			continue;
		}
		num[toAdd] = i + '0';
		if (toAdd != 0) {
			addAndMake(num, toAdd, halfLen, length);
		}
		else {
			formPalindrome(num, halfLen, length);
		}
	}
}

void createPalindromes(int length)
{
	int halfLen = length / 2;
	if (length % 2 == 1) {
		halfLen++;
	}
	char halfNum[12];

	addAndMake(halfNum, halfLen, halfLen, length);
}

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

void findPrimes(int max)
{
	primes.push_back(2);
	int maxPrime = sqrt(max);
	for (int i = 3; i <= maxPrime; i += 2) {
		if (checkPrime(i)) {
			primes.push_back(i);
		}
	}
}

void findPprimes()
{
	for (int i = 0; i < allPalindromes.size(); i++) {
		if (checkPrime(allPalindromes[i])) {
			pprimes.push_back(allPalindromes[i]);
		}
	}
}

int main()
{
	ifstream fin("pprime.in");
	ofstream fout("pprime.out");
	fin >> a;
	fin >> b;
	findPrimes(b);
	int startLen = findLength(a);
	int endLen = findLength(b);

	for (int i = startLen; i <= endLen; i++) {
		createPalindromes(i);
	}
	findPprimes();
	sort(pprimes.begin(), pprimes.end());
	for (int i = 0; i < pprimes.size(); i++) {
		fout << pprimes[i] << '\n';
	}
}