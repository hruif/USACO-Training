/*
ID: ruifanl1
TASK: fence3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

struct Fence {
	int x[2];
	int y[2];
	Fence() {

	}
	Fence(int x1, int y1, int x2, int y2) {
		x[0] = x1;
		y[0] = y1;
		x[1] = x2;
		y[1] = y2;
	}
};

int F, W, H;
Fence fences[150];
double ansX, ansY, ansDist = -1;

double square(double a) {
	return a * a;
}

double distToFences(double x, double y, int fenceIndex) {
	Fence& f = fences[fenceIndex];
	int left = f.x[0] < f.x[1] ? 0 : 1;
	int right = left ? 0 : 1;

	double rise = f.y[right] - f.y[left];
	double run = f.x[right] - f.x[left];
	double b;
	if (rise == 0) {
		double val = f.y[right] - y;
		if (val < 0) {
			val = -val;
		}
		if (x > f.x[right]) {
			val = sqrt(square(x - f.x[right]) + square(val));
		}
		else if (x < f.x[left]) {
			val = sqrt(square(f.x[left] - x) + square(val));
		}
		return val;
	}
	if (run == 0) {
		double val = f.x[right] - x;
		if (val < 0) {
			val = -val;
		}
		if (y > f.y[right] && y > f.y[left]) {
			val = sqrt(square(y - max(f.y[right], f.y[left])) + square(val));
		}
		else if (y < f.y[right] && y < f.y[left]) {
			val = sqrt(square(min(f.y[right], f.y[left]) - y) + square(val));
		}
		return val;
	}
	else {
		b = f.y[0] - (f.x[0] * rise / run);
	}

	double perpRise = -run;
	double perpRun = rise;
	double d = y - (x * perpRise / perpRun);

	double a;
	if (run == 0) {
		a = 0;
	}
	else {
		a = rise / run;
	}
	double c;
	if (perpRun == 0) {
		c = 0;
	}
	else {
		c = perpRise / perpRun;
	}

	a -= c;
	d -= b;

	double intersectX;
	if (a == 0) {
		intersectX = 0;
	}
	else {
		intersectX = d / a;
	}
	double intersectY = intersectX * a + b;

	double dist = sqrt(square(x - intersectX) + square(y - intersectY));
	return dist;
}

void solve() {
	double bestDist = -1;
	int bestX, bestY;
	for (int i = 0; i <= W; i++) {
		for (int j = 0; j <= H; j++) {
			double dist = 0;
			for (int k = 0; k < F; k++) {
				dist += distToFences(i, j, k);
			}
			//cout << dist << endl;
			if (dist < bestDist || bestDist == -1) {
				bestDist = dist;
				bestX = i;
				bestY = j;
			}
		}
	}

	for (double i = -0.5; i <= 0.5; i += 0.01) {
		double x = bestX + i;
		for (double j = -0.5; j <= 0.5; j += 0.01) {
			double dist = 0;
			double y = bestY + j;
			for (int k = 0; k < F; k++) {
				dist += distToFences(x, y, k);
			}
			//cout << dist << endl;
			if (dist < ansDist || ansDist == -1) {
				ansDist = dist;
				ansX = x;
				ansY = y;
			}
		}
	}
}

int main() {
	ifstream fin("fence3.in");
	fin >> F;
	for (int i = 0; i < F; i++) {
		int x1, y1, x2, y2;
		fin >> x1 >> y1 >> x2 >> y2;
		if (x1 > W) {
			W = x1;
		}
		if (x2 > W) {
			W = x2;
		}
		if (y1 > H) {
			H = y1;
		}
		if (y2 > H) {
			H = y2;
		}
		fences[i] = Fence(x1, y1, x2, y2);
	}
	solve();

	FILE* fout = fopen("fence3.out", "w");
	fprintf(fout, "%.1f %.1f %.1f\n", ansX, ansY, ansDist);
}