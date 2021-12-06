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

int countRect = 0;
int nextToCount = 0;

struct Rect {
	int x1;
	int y1;
	int x2;
	int y2;
	vector<int> nextTo;
	Rect(int x, int y, int X, int Y) {
		countRect++;
		x1 = x;
		y1 = y;
		x2 = X;
		y2 = Y;
	}
};

int N;
vector<Rect> rectangles;
vector<Rect> uncovered;

bool isBordering(Rect& a, Rect& b) {
	if (a.x1 > b.x2 || a.x2 < b.x1) {
		return false;
	}
	if (a.y1 < b.y2 || a.y2 > b.y1) {
		return false;
	}
	return true;

	/*
	if (a.x1 == b.x2) {
		if (a.y2 > b.y1 && a.y1 < b.y2) {
			return false;
		}
		return true;
	}
	if (a.x2 == b.x1) {
		if (a.y2 > b.y1 && a.y1 < b.y2) {
			return false;
		}
		return true;
	}
	if (a.y1 == b.y2) {
		if (a.x2 < b.x1 && a.x1 > b.x2) {
			return false;
		}
		return true;
	}
	if (a.y2 == b.y1) {
		if (a.x2 < b.x1 && a.x1 > b.x2) {
			return false;
		}
		return true;
	}
	return false;
	*/
}

void calc(Rect& a, Rect b, int bIndex, vector<Rect>& newRects) {
	if (b.x1 < a.x1) {
		b.x1 = a.x1;
	}
	if (b.y1 > a.y1) {
		b.y1 = a.y1;
	}
	if (b.x2 > a.x2) {
		b.x2 = a.x2;
	}
	if (b.y2 < a.y2) {
		b.y2 = a.y2;
	}

	Rect rect1(a.x1, a.y1, b.x1, a.y2);
	Rect rect2(b.x1, a.y1, b.x2, b.y1);
	Rect rect3(b.x1, b.y2, b.x2, a.y2);
	Rect rect4(b.x2, a.y1, a.x2, a.y2);

	if (rect1.x1 < rect1.x2 && rect1.y1 > rect1.y2) {
		for (int i = 0; i < a.nextTo.size(); i++) {
			if (isBordering(rect1, rectangles[a.nextTo[i]])) {
				rect1.nextTo.push_back(a.nextTo[i]);
				nextToCount++;
			}
		}
		rect1.nextTo.push_back(bIndex);
		nextToCount++;
		newRects.push_back(rect1);
	}
	if (rect2.x1 < rect2.x2 && rect2.y1 > rect2.y2) {
		for (int i = 0; i < a.nextTo.size(); i++) {
			if (isBordering(rect2, rectangles[a.nextTo[i]])) {
				rect2.nextTo.push_back(a.nextTo[i]);
				nextToCount++;
			}
		}
		rect2.nextTo.push_back(bIndex);
		nextToCount++;
		newRects.push_back(rect2);
	}
	if (rect3.x1 < rect3.x2 && rect3.y1 > rect3.y2) {
		for (int i = 0; i < a.nextTo.size(); i++) {
			if (isBordering(rect3, rectangles[a.nextTo[i]])) {
				rect3.nextTo.push_back(a.nextTo[i]);
				nextToCount++;
			}
		}
		rect3.nextTo.push_back(bIndex);
		nextToCount++;
		newRects.push_back(rect3);
	}
	if (rect4.x1 < rect4.x2 && rect4.y1 > rect4.y2) {
		for (int i = 0; i < a.nextTo.size(); i++) {
			if (isBordering(rect4, rectangles[a.nextTo[i]])) {
				rect4.nextTo.push_back(a.nextTo[i]);
				nextToCount++;
			}
		}
		rect4.nextTo.push_back(bIndex);
		nextToCount++;
		newRects.push_back(rect4);
	}
}

void addRect(Rect rect, int index) {
	vector<Rect> newUncovered;
	int top = rect.y1;
	int left = rect.x1;
	int bottom = rect.y2;
	int right = rect.x2;
	int size = uncovered.size();
	for (int i = 0; i < size; i++) {
		if (uncovered[i].x1 > right || uncovered[i].x2 < left || uncovered[i].y1 < bottom || uncovered[i].y2 > top) {
			continue;
		}
		if (uncovered[i].x1 == right || uncovered[i].x2 == left || uncovered[i].y1 == bottom || uncovered[i].y2 == top) {
			if (isBordering(uncovered[i], rect)) {
				uncovered[i].nextTo.push_back(index);
				nextToCount++;
			}
			continue;
		}
		calc(uncovered[i], rect, index, uncovered);
		uncovered.erase(uncovered.begin() + i);
		i--;
		size--;
	}
}

int findOverlap(vector<Rect>& rects, Rect original, int direction) {
	int totalOverlap = 0;
	vector<bool> flags(20001, false);
	if (rects.size() <= 1) {
		return 0;
	}
	if (direction == 0 || direction == 2) {
		for (int i = 0; i < rects.size(); i++) {
			int left = original.x1 < rects[i].x1 ? rects[i].x1 : original.x1;
			int right = original.x2 < rects[i].x2 ? original.x2 : rects[i].x2;
			for (int j = left; j < right; j++) {
				if (flags[j + 10000]) {
					totalOverlap++;
				}
				else {
					flags[j + 10000] = true;
				}
			}
		}
	}
	if (direction == 1 || direction == 3) {
		for (int i = 0; i < rects.size(); i++) {
			int top = original.y1 > rects[i].y1 ? rects[i].y1 : original.y1;
			int bottom = original.y2 > rects[i].y2 ? original.y2 : rects[i].y2;
			for (int j = bottom; j < top; j++) {
				if (flags[j + 10000]) {
					totalOverlap++;
				}
				else {
					flags[j + 10000] = true;
				}
			}
		}
	}
	return totalOverlap;
}

int sharedSides(Rect& a) {
	int total = 0;
	vector<vector<Rect>> shared(4); // rects found on the top (0), left (1), bottom (2), and right sides (3)
	for (int i = 0; i < a.nextTo.size(); i++) {
		Rect& b = rectangles[a.nextTo[i]];
		if (a.x1 == b.x2 || a.x2 == b.x1) {
			if (a.x1 == b.x2) {
				shared[1].push_back(b);
			}
			else {
				shared[3].push_back(b);
			}
			if (a.y1 >= b.y1 && a.y2 <= b.y2) {
				total += b.y1 - b.y2;
			}
			else if (b.y1 >= a.y1 && b.y2 <= a.y2) {
				total += a.y1 - a.y2;
			}
			else if (a.y1 > b.y1) {
				total += b.y1 - a.y2;
			}
			else {
				total += a.y1 - b.y2;
			}
		}
		if (a.y1 == b.y2 || a.y2 == b.y1) {
			if (a.y1 == b.y2) {
				shared[0].push_back(b);
			}
			else {
				shared[2].push_back(b);
			}
			if (a.x1 <= b.x1 && a.x2 >= b.x2) {
				total += b.x2 - b.x1;
			}
			else if (b.x1 <= a.x1 && b.x2 >= a.x2) {
				total += a.x2 - a.x1;
			}
			else if (a.x1 > b.x1) {
				total += b.x2 - a.x1;
			}
			else {
				total += a.x2 - b.x1;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		total -= findOverlap(shared[i], a, i);
	}
	return total;
}

int findPerimeter() {
	int perim = 0;
	for (int i = 0; i < uncovered.size(); i++) {
		perim += sharedSides(uncovered[i]);
	}
	return perim;
}

int main() {
	ifstream fin("picture.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, X, Y;
		fin >> x >> Y >> X >> y;
		Rect rect(x, y, X, Y);
		bool flag = false;
		for (int j = 0; j < rectangles.size(); j++) {
			if (rect.x1 >= rectangles[j].x1 && rect.y1 <= rectangles[j].y1 && rect.x2 <= rectangles[j].x2 && rect.y2 >= rectangles[j].y2) {
				flag = true;
				break;
			}
			if (rect.x1 <= rectangles[j].x1 && rect.y1 >= rectangles[j].y1 && rect.x2 >= rectangles[j].x2 && rect.y2 <= rectangles[j].y2) {
				rectangles.erase(rectangles.begin() + j);
				j--;
			}
		}
		if (flag) {
			continue;
		}
		rectangles.push_back(rect);
	}

	uncovered.push_back(Rect(-10000, 10000, 10000, -10000));
	for (int i = 0; i < rectangles.size(); i++) {
		addRect(rectangles[i], i);
	}
	int ans = findPerimeter();

	// stats
	int totalSize = 0;
	int totalSize2 = 0;
	for (int i = 0; i < uncovered.size(); i++) {
		totalSize += sizeof(uncovered[i].nextTo);
		totalSize2 += sizeof(uncovered[i]);
	}

	ofstream fout("picture.out");
	fout << ans << '\n';
	cout << endl << countRect << " " << nextToCount << "" << totalSize << " " << totalSize2 << endl;
}