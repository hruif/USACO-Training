#include <iostream>
#include <fstream>

using namespace std;

int n;
int photos[5][20000];
int nums[5][20001];
int nextNum[20001];
int original[20000];

int numCount[20001];
void findNext(int num) {
	for (int i = 0; i < 5; i++) {
		numCount[nums[i][num]]++;
	}
	for (int i = 0; i < 5; i++) {
		if (numCount[nums[i][num]] >= 3) {
			nextNum[num] = nums[i][num];
		}
		numCount[nums[i][num]] = 0;
	}
}

void buildOriginal() {
	int p = 1;
	int num = original[0];
	while (nextNum[num] != 0) {
		num = nextNum[num];
		original[p++] = num;
	}
}

bool prevNum[20001];
int main() {
	ifstream fin("photo.in");
	fin >> n;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < n; j++) {
			fin >> photos[i][j];
		}
		for (int j = 0; j < n - 1; j++) {
			nums[i][photos[i][j]] = photos[i][j + 1];
		}
	}

	for (int i = 1; i <= n; i++) {
		findNext(i);
	}
	for (int i = 1; i <= n; i++) {
		prevNum[nextNum[i]] = true;
	}
	for (int i = 1; i <= n; i++) {
		if (!prevNum[i]) {
			original[0] = i;
			break;
		}
	}
	buildOriginal();

	ofstream fout("photo.out");
	for (int i = 0; i < n; i++) {
		fout << original[i] << '\n';
	}
}