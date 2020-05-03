/*
ID: ruifanl1
TASK: lamps
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, C, solutions;
vector<int> on, off;
vector<bool> lamps;
vector<vector<bool>> output;
ofstream fout("lamps.out");

void sort() {
	int len = output.size();
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			for (int k = 0; k < lamps.size(); k++) {
				int val1 = output[i][k] ? 1 : 0;
				int val2 = output[j][k] ? 1 : 0;
				if (val1 != val2) {
					if (val1 > val2) {
						vector<bool> tmp = output[i];
						output[i] = output[j];
						output[j] = tmp;
					}
					break;
				}
			}
		}
	}
}

void printSolutions() {
	for (int i = 0; i < output.size(); i++) {
		for (int j = 0; j < N; j++) {
			fout << output[i][j];
		}
		fout << '\n';
	}
}

int powerOf2(int a) {
	int result = 1;
	for (int i = 0; i < a; i++) {
		result *= 2;
	}
	return result;
}

int binaryToInt() {
	int result = 1;
	for (int i = N - 1; i >= 0; i--) {
		result += powerOf2(i);
	}
	return result;
}

void isSolution(int counter) {
	if (counter > C || counter % 2 != C % 2) {
		return;
	}
	for (int i = 0; i < on.size(); i++) {
		if (!lamps[on[i] - 1]) {
			return;
		}
	}
	for (int i = 0; i < off.size(); i++) {
		if (lamps[off[i] - 1]) {
			return;
		}
	}
	solutions++;
	output.push_back(lamps);
}

void checkConfigs() {
	for (int p = 1; p >= 0; p--) {
		for (int i = 0; i < N; i++) {
			lamps[i] = !lamps[i];
		}
		isSolution(p);

		for (int i = 1; i >= 0; i--) {
			for (int j = 1; j < N; j += 2) {
				lamps[j] = !lamps[j];
			}
			if (i != 0) {
				isSolution(p + i);
			}

			for (int j = 1; j >= 0; j--) {
				for (int k = 0; k < N; k += 2) {
					lamps[k] = !lamps[k];
				}
				if (j != 0) {
					isSolution(p + i + j);
				}

				for (int k = 1; k >= 0; k--) {
					for (int l = 0; l < N; l += 3) {
						lamps[l] = !lamps[l];
					}
					if (k != 0) {
						isSolution(p + i + j + k);
					}
				}
			}
		}
	}
}

int main() {
	ifstream fin("lamps.in");
	fin >> N >> C;
	int buff = 0;
	fin >> buff;
	while (buff != -1) {
		on.push_back(buff);
		fin >> buff;
	}
	fin >> buff;
	while (buff != -1) {
		off.push_back(buff);
		fin >> buff;
	}

	for (int i = 0; i < N; i++) {
		lamps.push_back(true);
	}
	checkConfigs();
	sort();

	if (solutions == 0) {
		fout << "IMPOSSIBLE\n";
	}
	else {
		printSolutions();
	}
}