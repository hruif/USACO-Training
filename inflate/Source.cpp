/*
ID: ruifanl1
TASK: inflate
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int M, N;
int hm;
vector<double> ratios;
vector<int> pointers, combos;
vector<vector<int>> classes;

void sortClasses() {
	for (int i = 0; i < pointers.size() - 1; i++) {
		int tmpa = pointers[i];
		double a = ratios[tmpa];
		for (int j = i + 1; j < pointers.size(); j++) {
			int tmpb = pointers[j];
			if (a < ratios[tmpb]) {
				pointers[i] = tmpb;
				pointers[j] = tmpa;
				tmpa = pointers[i];
				a = ratios[pointers[i]];
			}
		}
	}
}

void findBest() {
	int best[2] = { -1, -1 };
	for (int i = 0; i < N; i++) {
		if (classes[i][0] > best[0] || best[0] == -1) {
			if (classes[i][1] < best[1] || best[1] == -1) {
				best[0] = classes[i][0];
				best[1] = classes[i][1];
			}
		}
	}
	for (int i = pointers.size() - 1; i >= 0; i--) {
		int p = pointers[i];
		if (classes[p][0] < best[0] && classes[p][1] > best[1]) {
			pointers.erase(pointers.begin() + i);
		}
	}
}

int findAns(int m, int p) {
	int ans = 0, timeLeft = m, lastp = -1;
	for (int i = 0; i < pointers.size(); i++) {
		int c = pointers[i];
		int time = m - classes[c][1];
		if (time >= 0) {
			lastp = i;
			if (m == 4535) {
				int ax = 5;
				ax -= 4;
			}
			int tmpAns = classes[c][0], t = combos[time];
			if (t != -1) {
				tmpAns += t;
			}
			else {
				tmpAns += findAns(time, i);
			}
			if (tmpAns > ans) {
				ans = tmpAns;
			}
		}
	}
	if (lastp == -1) {
		combos[m] = 0;
		return 0;
	}
	combos[m] = ans;
	return ans;
}

int main() {
	ifstream fin("inflate.in");
	fin >> M >> N;
	for (int i = 0; i < N; i++) {
		vector<int> classtmp;
		int tmp;
		fin >> tmp;
		classtmp.push_back(tmp);
		fin >> tmp;
		classtmp.push_back(tmp);
		double score = classtmp[0];
		double time = classtmp[1];
		ratios.push_back(score / time);
		classes.push_back(classtmp);
		pointers.push_back(i);
	}
	combos.resize(M + 1, -1);

	findBest();
	sortClasses();
	int ans = findAns(M, 0);

	ofstream fout("inflate.out");
	fout << ans << '\n';
}