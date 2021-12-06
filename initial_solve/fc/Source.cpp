/*
ID: ruifanl1
TASK: fc
LANG: C++
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

int N;
vector<pair<double, double>> locations;

void sortPerm(vector<int>& perm, vector<double>& angles) {
	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			if (angles[perm[i]] > angles[perm[j]]) {
				int tmpPerm = perm[i];
				perm[i] = perm[j];
				perm[j] = tmpPerm;
			}
		}
	}
}

double zCrossProd(int a1, int a2, int b1, int b2) {
	pair<double, double> u = locations[a1];
	u.first -= locations[a2].first;
	u.second -= locations[a2].second;

	pair<double, double> v = locations[b1];
	v.first -= locations[b2].first;
	v.second -= locations[b2].second;
	double a = u.first * v.second;
	double b = u.second * v.first;
	return a - b;
}

double findDist(pair<double, double> u, pair<double, double> v) {
	double a = u.first - v.first;
	double b = u.second - v.second;
	double dist = sqrt((a * a) + (b * b));
	return dist;
}

double findAns() {
	vector<double> angles(N);
	vector<int> perm(N);
	pair<double, double> mid;
	mid.first = 0;
	mid.second = 0;

	for (int i = 0; i < N; i++) {
		mid.first += locations[i].first / N;
		mid.second += locations[i].second / N;
	}

	for (int i = 0; i < N; i++) {
		angles[i] = atan2(locations[i].second - mid.second, locations[i].first - mid.first);
		perm[i] = i;
	}

	sortPerm(perm, angles);

	vector<int> hull(N);
	hull[0] = perm[0];
	hull[1] = perm[1];
	int hullpos = 2;
	for (int i = 2; i < N - 1; i++) {
		int p = perm[i];
		while (hullpos > 1 && zCrossProd(hull[hullpos - 2], hull[hullpos - 1], hull[hullpos - 1], p) < 0) {
			hullpos--;
		}
		hull[hullpos] = p;
		hullpos++;
	}

	int p = perm[N - 1];
	while (hullpos > 1 && zCrossProd(hull[hullpos - 2], hull[hullpos - 1], hull[hullpos - 1] , p) < 0) {
		hullpos--;
	}

	int hullstart = 0;
	bool flag;
	do {
		flag = false;
		if (hullpos - hullstart >= 2 && zCrossProd(p, hull[hullpos - 1], hull[hullstart], p) < 0) {
			p = hull[hullpos - 1];
			hullpos--;
			flag = true;
		}
		if (hullpos - hullstart >= 2 && zCrossProd(hull[hullstart], p, hull[hullstart + 1], hull[hullstart]) < 0) {
		hullstart++;
		flag = true;
		}
	} while (flag);
	hull[hullpos] = p;
	hullpos++;
	
	double ans = 0;
	for (int i = hullstart; i < hullpos; i++) {
		int before;
		if (i == hullstart) {
			before = hullpos - 1;
		}
		else {
			before = i - 1;
		}
		ans += findDist(locations[hull[i]], locations[hull[before]]);
	}
	return ans;
}

int main() {
	FILE* fin = fopen("fc.in", "r"), * fout = fopen("fc.out", "w");
	fscanf(fin, "%d", &N);
	for (int i = 0; i < N; i++) {
		pair<double, double> loc;
		double f, s;
		fscanf(fin, "%lf %lf", &f, &s);
		loc.first = f;
		loc.second = s;
		locations.push_back(loc);
	}
	fclose(fin);

	double ans = findAns();

	fprintf(fout, "%.2f\n", ans);
	fclose(fout);
}