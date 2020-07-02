/*
ID: ruifanl1
TASK: nuggets
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, original, largest, largestIndex;
vector<int> allPackages;
vector<bool> McNuggets;

void sortPackets() {
	int len = allPackages.size();
	for (int i = 0; i < len - 1; i++) {
		int p1 = allPackages[i];
		for (int j = i + 1; j < len; j++) {
			int p2 = allPackages[j];
			if (p2 < p1) {
				if (p1 == largest) {
					largestIndex = j;
				}
				if (p2 == largest) {
					largestIndex = i;
				}
				allPackages[j] = p1;
				allPackages[i] = p2;
				p1 = allPackages[i];
			}
		}
	}
}

void removeMultiples() {
	for (int i = 0; i < allPackages.size(); i++) {
		int p1 = allPackages[i];
		for (int j = 0; j < allPackages.size(); j++) {
			int p2 = allPackages[j];
			if (p2 % p1 == 0 && p1 != p2) {
				allPackages.erase(allPackages.begin() + j);
				j--;
			}
		}
	}
}

bool allEvens() {
	int len = allPackages.size();
	for (int i = 0; i < len; i++) {
		if (allPackages[i] % 2 == 1) {
			return false;
		}
	}
	return true;
}

int findLeast() {
	int least = -1;
	int len = allPackages.size();
	for (int i = 0; i < len; i++) {
		int package = allPackages[i];
		if (package < least || least == -1) {
			least = package;
		}
	}
	return least;
}

int findLargest() {
	int largest = -1;
	int len = allPackages.size();
	for (int i = 0; i < len; i++) {
		int p = allPackages[i];
		if (p > largest || largest == -1) {
			largestIndex = i;
			largest = p;
		}
	}
	return largest;
}

bool isPackageable(int a) {
	bool packageable = false;
	int len = allPackages.size();
	for (int i = 0; i <= largestIndex; i++) {
		int p1 = allPackages[i];
		int newA = a - allPackages[i];
		if (newA <= 0) {
			if (newA < 0) {
				return false;
			}
			return true;
		}
		for (int j = len - 1; j >= 0; j--) {
			int p2 = allPackages[j];
			if (p2 < newA) {
				break;
			}
			if (newA % p2 == 0 && newA != 0) {
				allPackages.push_back(a);
				return true;
			}
		}
	}
	return false;
}

int findAns() {
	int min = findLeast();
	largest = findLargest();
	if (min == 0) {
		return 0;
	}
	if (allEvens()) {
		return 0;
	}

	sortPackets();
	int multiplier = 1;
	int numPackaged = 0, numTimes = 0;
	while (true) {
		bool canBePackaged = true;
		int start = min * multiplier;
		for (int i = 0; i < min; i++) {
			if (!isPackageable(i + start)) {
				if (numPackaged == i) {
					numTimes++;
				}
				else {
					numTimes = 1;
					numPackaged = i;
				}
				canBePackaged = false;
			}
			if (start <= largest) {
				sortPackets();
			}
		}
		if (canBePackaged) {
			break;
		}
		if (numTimes > largest * largest) {
			return 0;
		}
		multiplier++;
	}
	for (int i = min * multiplier; i >= min * (multiplier - 1); i--) {
		if (!isPackageable(i)) {
			return i;
		}
	}
	return min - 1;
}

int main() {
	ifstream fin("nuggets.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		fin >> tmp;
		allPackages.push_back(tmp);
	}

	removeMultiples();

	int ans = 0;
	original = allPackages.size();
	if (original > 1) {
		ans = findAns();
	}

	ofstream fout("nuggets.out");
	fout << ans << '\n';
}