/*
ID: ruifanl1
TASK: packrec
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

struct Rect {
	int w;
	int h;
	Rect(int w, int h) {
		this->w = w;
		this->h = h;
	}
	Rect() {

	}
};

int smallest = -1;
Rect rects[4];
vector<Rect> solutions;

void checkBest(int w, int h) {
	int area = w * h;
	if (area == smallest) {
		solutions.push_back(Rect(w, h));
	}
	else if (area < smallest || smallest == -1) {
		smallest = area;
		solutions.clear();
		solutions.push_back(Rect(w, h));
	}
}

void layout1(Rect r1, Rect r2, Rect r3, Rect r4) {
	int w = r1.w + r2.w + r3.w + r4.w;
	int h = max(max(r1.h, r2.h), max(r3.h, r4.h));
	checkBest(w, h);
}

void layout2(Rect r1, Rect r2, Rect r3, Rect r4) {
	// r1 - bottom
	int w = max(r1.w, r2.w + r3.w + r4.w);
	int h = r1.h + max(r2.h, max(r3.h, r4.h));
	checkBest(w, h);
}

void layout3(Rect r1, Rect r2, Rect r3, Rect r4) {
	// r1 - bottom
	// r2 - side
	int w = max(r1.w, r3.w + r4.w) + r2.w;
	int h = max(r1.h + max(r3.h, r4.h), r2.h);
	checkBest(w, h);
}

void layout4_5(Rect r1, Rect r2, Rect r3, Rect r4) {
	// r1 - bottom
	// r2 - top
	int w = max(r1.w, r2.w) + r3.w + r4.w;
	int h = max(max(r1.h + r2.h, r3.h), r4.h);
	checkBest(w, h);
}

void layout6(Rect r1, Rect r2, Rect r3, Rect r4) {
	// r1 - vertical top
	// r2 - horizontal top
	// r3 - below vertical
	// r4 - below horizontal
	int w1 = r1.w;
	if (r4.h > r3.h) {
		w1 += r4.w;
	}
	else {
		w1 += r2.w;
	}
	int w2 = r2.w;
	if (r3.h > r4.h) {
		w2 += r3.w;
	}
	else {
		w2 += r1.w;
	}
	int w =  max(max(w1, w2), r3.w + r4.w);
	int h = max(r1.h + r3.h, r2.h + r4.h);
	checkBest(w, h);
}

void placeRects() {
	bool placed[4];
	memset(placed, false, 4);
	for (int i = 0; i < 4; i++) {
		placed[i] = true;
		Rect r1 = rects[i];

		for (int j = 0; j < 4; j++) {
			if (placed[j]) {
				continue;
			}

			placed[j] = true;
			Rect r2 = rects[j];

			for (int k = 0; k < 4; k++) {
				if (placed[k]) {
					continue;
				}

				placed[k] = true;
				Rect r3 = rects[k];
				
				for (int l = 0; l < 4; l++) {
					if (placed[l]) {
						continue;
					}

					Rect r4 = rects[l];

					layout1(r1, r2, r3, r4);
					layout2(r1, r2, r3, r4);
					layout3(r1, r2, r3, r4);
					layout4_5(r1, r2, r3, r4);
					layout6(r1, r2, r3, r4);
				}

				placed[k] = false;
			}

			placed[j] = false;
		}

		placed[i] = false;
	}
}

void findRects() {
	for (int i = 0; i < 2; i++) {
		int t0 = rects[0].w;
		rects[0].w = rects[0].h;
		rects[0].h = t0;
		for (int j = 0; j < 2; j++) {
			int t1 = rects[1].w;
			rects[1].w = rects[1].h;
			rects[1].h = t1;
			for (int k = 0; k < 2; k++) {
				int t2 = rects[2].w;
				rects[2].w = rects[2].h;
				rects[2].h = t2;
				for (int l = 0; l < 2; l++) {
					int t3 = rects[3].w;
					rects[3].w = rects[3].h;
					rects[3].h = t3;
					placeRects();
				}
			}
		}
	}
}

void fixWH() { // ensuring width < height for all
	for (int i = 0; i < solutions.size(); i++) {
		if (solutions[i].w > solutions[i].h) {
			int t = solutions[i].w;
			solutions[i].w = solutions[i].h;
			solutions[i].h = t;
		}
	}
}

void removeDuplicates() {
	for (int i = 0; i < solutions.size() - 1; i++) {
		for (int j = i + 1; j < solutions.size(); j++) {
			Rect r1 = solutions[i];
			Rect r2 = solutions[j];
			if (r1.w == r2.w && r1.h == r2.h) {
				solutions.erase(solutions.begin() + j);
				j--;
			}
		}
	}
}

void sortSolution() {
	for (int i = 0; i < solutions.size() - 1; i++) {
		for (int j = i + 1; j < solutions.size(); j++) {
			if (solutions[i].w > solutions[j].w) {
				Rect r = solutions[i];
				solutions[i] = solutions[j];
				solutions[j] = r;
			}
		}
	}
}

int main() {
	ifstream fin("packrec.in");
	for (int i = 0; i < 4; i++) {
		Rect t;
		fin >> t.w >> t.h;
		if (t.w > t.h) {
			int tmp = t.w;
			t.w = t.h;
			t.h = tmp;
		}
		rects[i] = t;
	}

	findRects();
	fixWH();
	removeDuplicates();
	sortSolution();

	ofstream fout("packrec.out");
	fout << smallest << '\n';
	for (int i = 0; i < solutions.size(); i++) {
		fout << solutions[i].w << ' ' << solutions[i].h << '\n';
	}
}