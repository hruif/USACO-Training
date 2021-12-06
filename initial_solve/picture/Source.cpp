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

int cR = 0;
int cRa = 0;

struct Rect {
	short x1;
	short y1;
	short x2;
	short y2;
	unsigned char bits; // 0, 1, 2, 3: left, right, bottom, top
	Rect(int x, int y, int X, int Y) {
		cR++;
		x1 = x;
		y1 = y;
		x2 = X;
		y2 = Y;
		bits = 0;
	}
	Rect(Rect& a, int x, int y, int X, int Y) {
		cRa++;
		x1 = x;
		y1 = y;
		x2 = X;
		y2 = Y;
		bits = 0;
		if (x1 == a.x1) {
			bits = (bits & 0b1110) | (a.bits & 0b0001);
		}
		if (x2 == a.x2) {
			bits = (bits & 0b1101) | (a.bits & 0b0010);
		}
		if (y1 == a.y1) {
			bits = (bits & 0b1011) | (a.bits & 0b0100);
		}
		if (y2 == a.y2) {
			bits = (bits & 0b0111) | (a.bits & 0b1000);
		}
	}
};

int N;

bool isProper(Rect& r) {
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

	Rect* rect1 = a.x1 < b.x1&& a.y1 < b.y1 ? new Rect(a, a.x1, a.y1, b.x1, b.y1) : nullptr;
	Rect* rect2 = b.x1 < b.x2&& a.y1 < b.y1 ? new Rect(a, b.x1, a.y1, b.x2, b.y1) : nullptr;
	Rect* rect3 = b.x2 < a.x2&& a.y1 < b.y1 ? new Rect(a, b.x2, a.y1, a.x2, b.y1) : nullptr;
	Rect* rect4 = a.x1 < b.x1&& b.y1 < b.y2 ? new Rect(a, a.x1, b.y1, b.x1, b.y2) : nullptr;
	Rect* rect5 = b.x2 < a.x2&& b.y1 < b.y2 ? new Rect(a, b.x2, b.y1, a.x2, b.y2) : nullptr;
	Rect* rect6 = a.x1 < b.x1&& b.y2 < a.y2 ? new Rect(a, a.x1, b.y2, b.x1, a.y2) : nullptr;
	Rect* rect7 = b.x1 < b.x2&& b.y2 < a.y2 ? new Rect(a, b.x1, b.y2, b.x2, a.y2) : nullptr;
	Rect* rect8 = b.x2 < a.x2&& b.y2 < a.y2 ? new Rect(a, b.x2, b.y2, a.x2, a.y2) : nullptr;

	if (rect1) {
		newRects.push_back(rect1);
	}
	else {
		delete rect1;
	}
	if (rect3) {
		newRects.push_back(rect3);
	}
	else {
		delete rect3;
	}
	if (rect6) {
		newRects.push_back(rect6);
	}
	else {
		delete rect6;
	}
	if (rect8) {
		newRects.push_back(rect8);
	}
	else {
		delete rect8;
	}
	if (rect2) {
		rect2->bits = rect2->bits | 0b1000;
		newRects.push_back(rect2);
	}
	else {
		delete rect2;
	}
	if (rect4) {
		rect4->bits = rect4->bits | 0b0010;
		newRects.push_back(rect4);
	}
	else {
		delete rect4;
	}
	if (rect5) {
		rect5->bits = rect5->bits | 0b0001;
		newRects.push_back(rect5);
	}
	else {
		delete rect5;
	}
	if (rect7) {
		rect7->bits = rect7->bits | 0b0100;
		newRects.push_back(rect7);
	}
	else {
		delete rect7;
	}
}

void addRect(Rect rect, vector<Rect*>& white) {
	int size = white.size();
	for (int i = 0; i < size; i++) {
		auto r = white[i];
		if (r->x1 > rect.x2 || r->x2 < rect.x1 || r->y1 > rect.y2 || r->y2 < rect.y1) {
			continue;
		}
		calc(*r, rect, white);
		delete white[i];
		white.erase(white.begin() + i);
		i--;
		size--;
	}
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



void Simplify(vector<Rect>& rs) {
	// sort
	int n = rs.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (rs[i].x1 < rs[j].x1) {
				continue;
			}
			if (rs[i].x1 > rs[j].x1 || rs[i].y1 > rs[j].y1 || rs[i].y1 == rs[j].y1 &&
				(rs[i].x2 > rs[j].x2 || rs[i].x2 == rs[j].x2 && rs[i].y2 > rs[j].y2)) {
				Rect t = rs[i];
				rs[i] = rs[j];
				rs[j] = t;
			}
		}
	}

	// merge
	vector<Rect> rects;
	for (int i = n - 1; i >= 0; i--) {
		bool del = false;
		for (int j = 0; j < i; j++) {
			if (rs[i].x1 >= rs[j].x1
				&& rs[i].x2 <= rs[j].x2
				&& rs[i].y1 >= rs[j].y1
				&& rs[i].y2 <= rs[j].y2) {
				del = true;
				break;
			}
		}
		if (!del) {
			rects.push_back(move(rs[i]));
		}
	}
	rs = move(rects);
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

	Simplify(rectangles);

	Rect* initialRect = new Rect(-10001, -10001, 10001, 10001);
	uncovered.push_back(initialRect);
	for (int i = 0; i < rectangles.size(); i++) {
		addRect(rectangles[i], uncovered);
	}
	int ans = findPerimeter(uncovered);

	ofstream fout("picture.out");
	fout << ans << '\n';
	cout << sizeof(uncovered) << ' ' << cR << ' ' << cRa;
}
