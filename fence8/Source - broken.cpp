/*
ID: ruifanl1
TASK: fence8
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool found = false;
int N, R, total;
vector<int> boards;
vector<int> rails;

void sortVector(vector<int>& a) {
	for (int i = 0; i < a.size() - 1; i++) {
		for (int j = i + 1; j < a.size(); j++) {
			if (a[i] > a[j]) {
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}

int findCuts(vector<bool>& cutRails, int b) {
	int firstRail;
	int size = boards[b];
	for (firstRail = rails.size() - 1; firstRail >= 0; firstRail--) {
		if (!cutRails[firstRail] && rails[firstRail] <= size) {
			break;
		}
	}
	if (firstRail == -1) {
		return 0;
	}
	int totalCut = 0;
	int bestPos = firstRail;
	int len = 0;
	int alreadyCut = 0;
	int bestTotal = 0;
	int bestCut = 0;
	for (int i = firstRail; i >= 0; i--) {
		if (cutRails[i]) {
			alreadyCut++;
			continue;
		}
		totalCut += rails[i];
		if (totalCut > size) {
			totalCut -= rails[firstRail--];
			while (cutRails[firstRail]) {
				alreadyCut--;
				firstRail--;
			}
		}
		else {
			bestPos = firstRail;
			len++;
			bestTotal = totalCut;
			bestCut = alreadyCut;
		}
	}
	alreadyCut = bestCut;
	totalCut = bestTotal;
	firstRail = bestPos;
	for (int i = firstRail - ((len - 1) + alreadyCut); i <= firstRail; i++) {
		if (cutRails[i]) {
			continue;
		}
		while (totalCut <= size) {
			int oI = i;
			int oFR = firstRail;
			totalCut -= rails[i++];
			while (i < rails.size() && cutRails[i]) {
				i++;
			}
			do {
				firstRail++;
			} while (firstRail < rails.size() && cutRails[firstRail]);
			if (i == rails.size() || firstRail == rails.size()) {
				i = oI;
				firstRail = oFR;
				totalCut += rails[i];
				break;
			}
			totalCut += rails[firstRail];
		}
		if (totalCut > size) {
			totalCut -= rails[firstRail];
			do {
				i--;
			} while (cutRails[i]);
			do {
				firstRail--;
			} while (cutRails[i]);
			totalCut += rails[i];
		}
		cutRails[i] = true;
	}

	return len;
}

int solve() {
	vector<bool> cutRails(rails.size(), false);
	vector<int> railsInBoards(boards.size(), 0);
	int ans = 0;
	for (int i = 0; i < boards.size(); i++) {
		ans += findCuts(cutRails, i);
	}
	return ans;
}

int main() {
	ifstream fin("fence8.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int t;
		fin >> t;
		total += t;
		boards.push_back(t);
	}
	fin >> R;
	for (int i = 0; i < R; i++) {
		int t;
		fin >> t;
		rails.push_back(t);
	}

	vector<bool> cut(R, false);
	
	sortVector(rails);
	sortVector(boards);
	int r = 0;
	for (int i = 0; i < 29; i++) {
		r += rails[i];
	}
	int b = 0;
	for (int i = 0; i < 10; i++) {
		b += boards[i];
	}
	cout << r << ' ' << b;
	int ans = solve();

	ofstream fout("fence8.out");
	fout << ans << '\n';
}