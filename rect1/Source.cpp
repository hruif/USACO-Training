/*
ID: ruifanl1
TASK: rect1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rect {
	int x1;
	int y1;
	int x2;
	int y2;
	int color;
	Rect(int x1, int y1, int x2, int y2, int color) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		this->color = color;
	}
	Rect() {

	}
};

int A, B, N;
int areas[2501];
vector<Rect> opaques;
vector<Rect> allRects;

void splitRect(Rect& b, Rect c, vector<Rect>& newR) { // bottom and covering rectangle
	if (b.x1 > c.x1) {
		c.x1 = b.x1;
	}
	if (b.x2 < c.x2) {
		c.x2 = b.x2;
	}
	if (b.y1 > c.y1) {
		c.y1 = b.y1;
	}
	if (b.y2 < c.y2) {
		c.y2 = b.y2;
	}

	Rect r1(b.x1, b.y1, c.x1, b.y2, b.color);
	Rect r2(c.x1, c.y2, c.x2, b.y2, b.color);
	Rect r3(c.x1, b.y1, c.x2, c.y1, b.color);
	Rect r4(c.x2, b.y1, b.x2, b.y2, b.color);

	if (r1.x1 < r1.x2 && r1.y1 < r1.y2) {
		newR.push_back(r1);
	}
	if (r2.x1 < r2.x2 && r2.y1 < r2.y2) {
		newR.push_back(r2);
	}
	if (r3.x1 < r3.x2 && r3.y1 < r3.y2) {
		newR.push_back(r3);
	}
	if (r4.x1 < r4.x2 && r4.y1 < r4.y2) {
		newR.push_back(r4);
	}
}

void addRect(Rect r) {
	vector<Rect> newRects;
	for (int i = 0; i < allRects.size(); i++) {
		Rect& next = allRects[i];
		if (next.x1 >= r.x2 || r.x1 >= next.x2 || next.y1 >= r.y2 || r.y1 >= next.y2) {
			newRects.push_back(move(next));
			continue;
		}
		splitRect(next, r, newRects);
	}
	newRects.push_back(r);
	allRects = move(newRects);
}

void findAreas() {
	for (int i = 0; i < allRects.size(); i++) {
		Rect& r = allRects[i];
		int w = r.x2 - r.x1;
		int h = r.y2 - r.y1;
		int area = w * h;
		areas[r.color] += area;
	}
}

int main() {
	ifstream fin("rect1.in");
	fin >> A >> B >> N;
	for (int i = 0; i < N; i++) {
		Rect r;
		fin >> r.x1 >> r.y1 >> r.x2 >> r.y2 >> r.color;
		opaques.push_back(r);
	}

	Rect sheet(0, 0, A, B, 1);
	allRects.push_back(sheet);
	for (int i = 0; i < N; i++) {
		addRect(opaques[i]);
	}
	findAreas();

	ofstream fout("rect1.out");
	for (int i = 0; i < 2501; i++) {
		if (areas[i] > 0) {
			fout << i << ' ' << areas[i] << '\n';
		}
	}
}