/*
ID: ruifanl1
TASK: picture
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

struct Rect {
	short x1;
	short y1;
	short x2;
	short y2;
	unsigned char bits; // 0, 1, 2, 3: left, right, bottom, top
	Rect(int x, int y, int X, int Y) {
		x1 = x;
		y1 = y;
		x2 = X;
		y2 = Y;
		bits = 0;
	}
	Rect(Rect& a, int x, int y, int X, int Y) {
		x1 = x;
		y1 = y;
		x2 = X;
		y2 = Y;
		if (x1 == a.x1) {
			bits = (bits & 0b1110) | (a.bits & 0b0001);
		}
		else {
			bits = (bits & 0b1110);
		}
		if (x2 == a.x2) {
			bits = (bits & 0b1101) | (a.bits & 0b0010);
		}
		else {
			bits = (bits & 0b1101);
		}
		if (y1 == a.y1) {
			bits = (bits & 0b1011) | (a.bits & 0b0100);
		}
		else {
			bits = (bits & 0b1011);
		}
		if (y2 == a.y2) {
			bits = (bits & 0b0111) | (a.bits & 0b1000);
		}
		else {
			bits = (bits & 0b0111);
		}
	}
};

int N;

bool isProper(Rect& r, Rect& a) {
	if (r.x1 >= r.x2 || r.y1 >= r.y2) {
		return false;
	}
	return true;
}

void calc(Rect& a, Rect b, vector<Rect*>& newRects) {
	if (b.x1 < a.x1) {
		b.x1 = a.x1;
	}
	if (b.y1 < a.y1) {
		b.y1 = a.y1;
	}
	if (b.x2 > a.x2) {
		b.x2 = a.x2;
	}
	if (b.y2 > a.y2) {
		b.y2 = a.y2;
	}

	Rect* rect1 = new Rect(a, a.x1, a.y1, b.x1, b.y1);
	Rect* rect2 = new Rect(a, b.x1, a.y1, b.x2, b.y1);
	Rect* rect3 = new Rect(a, b.x2, a.y1, a.x2, b.y1);
	Rect* rect4 = new Rect(a, a.x1, b.y1, b.x1, b.y2);
	Rect* rect5 = new Rect(a, b.x2, b.y1, a.x2, b.y2);
	Rect* rect6 = new Rect(a, a.x1, b.y2, b.x1, a.y2);
	Rect* rect7 = new Rect(a, b.x1, b.y2, b.x2, a.y2);
	Rect* rect8 = new Rect(a, b.x2, b.y2, a.x2, a.y2);

	if (isProper(*rect1, a)) {
		newRects.push_back(rect1);
	}
	else {
		delete rect1;
	}
	if (isProper(*rect3, a)) {
		newRects.push_back(rect3);
	}
	else {
		delete rect3;
	}
	if (isProper(*rect6, a)) {
		newRects.push_back(rect6);
	}
	else {
		delete rect6;
	}
	if (isProper(*rect8, a)) {
		newRects.push_back(rect8);
	}
	else {
		delete rect8;
	}
	if (isProper(*rect2, a)) {
		rect2->bits = rect2->bits | 0b1000;
		newRects.push_back(rect2);
	}
	else {
		delete rect2;
	}
	if (isProper(*rect4, a)) {
		rect4->bits = rect4->bits | 0b0010;
		newRects.push_back(rect4);
	}
	else {
		delete rect4;
	}
	if (isProper(*rect5, a)) {
		rect5->bits = rect5->bits | 0b0001;
		newRects.push_back(rect5);
	}
	else {
		delete rect5;
	}
	if (isProper(*rect7, a)) {
		rect7->bits = rect7->bits | 0b0100;
		newRects.push_back(rect7);
	}
	else {
		delete rect7;
	}
}

void addRect(Rect rect, vector<Rect*>& white) {
	vector<Rect*> rects;
	for (int i = 0; i < white.size(); i++) {
		auto r = white[i];
		if (r->x1 > rect.x2 || r->x2 < rect.x1 || r->y1 > rect.y2 || r->y2 < rect.y1) {
			rects.push_back(r);
			continue;
		}
		calc(*white[i], rect, rects);
		delete white[i];
	}
	white = move(rects);
}

int findPerimeter(vector<Rect*>& white) {
	int perim = 0;
	for (int i = 0; i < white.size(); i++) {
		auto r = *white[i];
		if (r.bits & 0b0100) {
			perim += r.x2 - r.x1;
		}
		if (r.bits & 0b1000) {
			perim += r.x2 - r.x1;
		}
		if (r.bits & 0b0001) {
			perim += r.y2 - r.y1;
		}
		if (r.bits & 0b0010) {
			perim += r.y2 - r.y1;
		}
	}
	return perim;
}

int main() {
	vector<Rect> rectangles;
	vector<Rect*> uncovered;

	ifstream fin("picture.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, X, Y;
		fin >> x >> y >> X >> Y;
		Rect rect(x, y, X, Y);
		rectangles.push_back(move(rect));
	}

	Rect* initialRect = new Rect(-10000, -10000, 10000, 10000);
	uncovered.push_back(initialRect);
	for (int i = 0; i < rectangles.size(); i++) {
		addRect(rectangles[i], uncovered);
	}
	int ans = findPerimeter(uncovered);

	ofstream fout("picture.out");
	fout << ans << '\n';
}