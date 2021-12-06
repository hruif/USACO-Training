/*
ID: ruifanl1
TASK: window
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct window {
	int x;
	int y;
	int X;
	int Y;
	window() {
		x = y = X = Y = -1;
	}
	window(int x, int y, int X, int Y) {
		this->x = x;
		this->y = y;
		this->X = X;
		this->Y = Y;
	}
};

vector<window> windows(62);
vector<vector<int>> allBelow(62); // which windows are below current
vector<vector<int>> allAbove(62);
vector<vector<bool>> isAbove(62, vector<bool>(62));
vector<vector<bool>> isBelow(62, vector<bool>(62)); // is a window below others
vector<bool> placed(62);

int IToIndex(char I) {
	int index;
	if (I <= '9') {
		index = I - '0';
	}
	else if (I <= 'Z') {
		index = I - 'A' + 10;
	}
	else {
		index = I - 'a' + 36;
	}
	return index;
}

void w(char I, int x, int y, int X, int Y) {
	window next(x, y, X, Y);
	int index = IToIndex(I);
	windows[index] = next;

	for (int i = 0; i < 62; i++) {
		if (placed[i]) {
			isAbove[index][i] = true;
			isBelow[i][index] = true;
			isBelow[index][i] = false;
			isAbove[i][index] = false;
			allAbove[i].push_back(index);
			allBelow[index].push_back(i);
		}
	}
	placed[index] = true;
}

void t(char I) {
	int index = IToIndex(I);

	for (int i = 0; i < 62; i++) {
		if (placed[i] && !isBelow[i][index]) {
			isAbove[index][i] = true;
			isBelow[i][index] = true;
			isBelow[index][i] = false;
			isAbove[i][index] = false;
			allAbove[i].push_back(index);
			allBelow[index].push_back(i);
		}
	}
	for (int i = 0; i < allAbove[index].size(); i++) {
		int next = allAbove[index][i];
		isAbove[next][index] = false;
		for (int j = 0; j < allBelow[next].size(); j++) {
			if (allBelow[next][j] == index) {
				allBelow[next].erase(allBelow[next].begin() + j);
				break;
			}
		}
	}
	allAbove[index].clear();
}

void b(char I) {
	int index = IToIndex(I);

	for (int i = 0; i < 62; i++) {
		if (placed[i] && !isAbove[i][index]) {
			isBelow[index][i] = true;
			isAbove[index][i] = false;
			isBelow[i][index] = false;
			isAbove[i][index] = true;
			allAbove[index].push_back(i);
			allBelow[i].push_back(index);
		}
	}
	for (int i = 0; i < allBelow[index].size(); i++) {
		int next = allBelow[index][i];
		isBelow[next][index] = false;
		for (int j = 0; j < allAbove[next].size(); j++) {
			if (allAbove[next][j] == index) {
				allAbove[next].erase(allAbove[next].begin() + j);
				break;
			}
		}
	}
	allBelow[index].clear();
}

void d(char I) {
	int index = IToIndex(I);

	for (int i = 0; i < allAbove[index].size(); i++) {
		int next = allAbove[index][i];
		isAbove[next][index] = false;
		for (int j = 0; j < allBelow[next].size(); j++) {
			if (allBelow[next][j] == index) {
				allBelow[next].erase(allBelow[next].begin() + j);
				break;
			}
		}
	}
	allAbove[index].clear();
	for (int i = 0; i < allBelow[index].size(); i++) {
		int next = allBelow[index][i];
		isBelow[next][index] = false;
		for (int j = 0; j < allAbove[next].size(); j++) {
			if (allAbove[next][j] == index) {
				allAbove[next].erase(allAbove[next].begin() + j);
				break;
			}
		}
	}
	allBelow[index].clear();
}

void cover(vector<window>& uncovered, int index) {
	vector<window> toAdd;
	for (int i = 0; i < uncovered.size(); i++) {
		int left = uncovered[i].x;
		int right = uncovered[i].X;
		if (left > right) {
			int tmp = left;
			left = right;
			right = tmp;
		}
		int top = uncovered[i].y;
		int bottom = uncovered[i].Y;
		if (top > bottom) {
			int tmp = top;
			top = bottom;
			bottom = tmp;
		}
		int w = right - left;
		int h = bottom - top;

		int coverLeft = windows[index].x;
		int coverRight = windows[index].X;
		if (coverLeft > coverRight) {
			int tmp = coverLeft;
			coverLeft = coverRight;
			coverRight = tmp;
		}
		int coverTop = windows[index].y;
		int coverBottom = windows[index].Y;
		if (coverTop > coverBottom) {
			int tmp = coverTop;
			coverTop = coverBottom;
			coverBottom = tmp;
		}

		if (coverLeft >= right || coverRight <= left || coverTop >= bottom || coverBottom <= top) {
			continue;
		}

		int newLeft;
		int newRight;
		int newTop;
		int newBot;
		if (coverLeft < left) {
			newLeft = left;
		}
		else {
			newLeft = coverLeft;
		}
		if (coverRight > right) {
			newRight = right;
		}
		else {
			newRight = coverRight;
		}
		if (coverTop < top) {
			newTop = top;
		}
		else {
			newTop = coverTop;
		}
		if (coverBottom > bottom) {
			newBot = bottom;
		}
		else {
			newBot = coverBottom;
		}
		uncovered.erase(uncovered.begin() + i);
		i--;
		if (newLeft == left && newRight == right && newTop == top && newBot == bottom) {
			continue;
		}
		if (newLeft == newRight || newTop == newBot) {
			continue;
		}

		if (newLeft == left) {
			window p1, p2;
			p1.x = newRight;
			p1.X = right;
			p2.x = left;
			p2.X = right;
			if (newTop == top) {
				p1.y = top;
				p1.Y = newBot;
				p2.y = newBot;
				p2.Y = bottom;
			}
			else if (newBot == bottom) {
				p1.y = newTop;
				p1.Y = bottom;
				p2.y = top;
				p2.Y = newTop;
			}
			else {
				window p3(left, top, right, newTop);
				if (p3.x != p3.X && p3.y != p3.Y) {
					toAdd.push_back(p3);
				}
				p1.y = newTop;
				p1.Y = newBot;
				p2.y = newBot;
				p2.Y = bottom;
			}
			if (p1.x != p1.X && p1.y != p1.Y) {
				toAdd.push_back(p1);
			}
			if (p2.x != p2.X && p2.y != p2.Y) {
				toAdd.push_back(p2);
			}
		}
		else if (newRight == right) {
			window p1, p2;
			p1.x = left;
			p1.X = newLeft;
			p2.x = left;
			p2.X = right;
			if (newTop == top) {
				p1.y = top;
				p1.Y = newBot;
				p2.y = newBot;
				p2.Y = bottom;
			}
			else if (newBot == bottom) {
				p1.y = newTop;
				p1.Y = bottom;
				p2.y = top;
				p2.Y = newTop;
			}
			else {
				window p3(left, top, right, newTop);
				if (p3.x != p3.X && p3.y != p3.Y) {
					toAdd.push_back(p3);
				}
				p1.y = newTop;
				p1.Y = newBot;
				p2.y = newBot;
				p2.Y = bottom;
			}
			if (p1.x != p1.X && p1.y != p1.Y) {
				toAdd.push_back(p1);
			}
			if (p2.x != p2.X && p2.y != p2.Y) {
				toAdd.push_back(p2);
			}
		}
		else {
			window p1(left, top, newLeft, bottom);
			window p2(newRight, top, right, bottom);
			window p3;
			p3.x = newLeft;
			p3.X = newRight;
			if (newTop == top) {
				p3.y = newBot;
				p3.Y = bottom;
			}
			else if (newBot == bottom) {
				p3.y = top;
				p3.Y = newTop;
			}
			else {
				window p4(newLeft, top, newRight, newTop);
				if (p4.x != p4.X && p4.y != p4.Y) {
					toAdd.push_back(p4);
				}
				p3.y = newBot;
				p3.Y = bottom;
			}
			if (p1.x != p1.X && p1.y != p1.Y) {
				toAdd.push_back(p1);
			}
			if (p2.x != p2.X && p2.y != p2.Y) {
				toAdd.push_back(p2);
			}
			if (p3.x != p3.X && p3.y != p3.Y) {
				toAdd.push_back(p3);
			}
		}
		for (int i = 0; i < toAdd.size(); i++) {
			uncovered.push_back(toAdd[i]);
		}
		toAdd.clear();
	}
}

void s(char I, FILE*& fout) {
	int index = IToIndex(I);
	int left = windows[index].x;
	int right = windows[index].X;
	if (left > right) {
		int tmp = left;
		left = right;
		right = tmp;
	}
	int top = windows[index].y;
	int bottom = windows[index].Y;
	if (top > bottom) {
		int tmp = top;
		top = bottom;
		bottom = tmp;
	}

	vector<window> uncovered;
	uncovered.push_back(windows[index]);

	for (int i = 0; i < allAbove[index].size(); i++) {
		cover(uncovered, allAbove[index][i]);
	}

	int unCcovered = 0;
	for (int i = 0; i < uncovered.size(); i++) {
		int w = uncovered[i].x - uncovered[i].X;
		int h = uncovered[i].y - uncovered[i].Y;
		if (w < 0) {
			w = -w;
		}
		if (h < 0) {
			h = -h;
		}
		unCcovered += w * h;
	}
	int width = right - left;
	int height = bottom - top;
	float total = width * height;
	float c = unCcovered;
	float ratio = unCcovered / total;
	float percentage = ratio * 100;
	fprintf(fout, "%.3f\n", percentage);
}

int main() {
	ifstream fin("window.in");
	FILE* fout = fopen("window.out", "w");
	char next;
	while (fin >> next) {
		if (next == '\n') {
			continue;
		}
		if (next == 'w') {
			char I;
			int x, y, X, Y;
			vector<char> commas(4);
			char p;
			fin >> p;
			fin >> I >> commas[0] >> x >> commas[1] >> y >> commas[2] >> X >> commas[3] >> Y;
			fin >> p;
			w(I, x, y, X, Y);
		}
		if (next == 't') {
			char I;
			char p;
			fin >> p;
			fin >> I;
			fin >> p;
			t(I);
		}
		if (next == 'b') {
			char I;
			char p;
			fin >> p;
			fin >> I;
			fin >> p;
			b(I);
		}
		if (next == 'd') {
			char I;
			char p;
			fin >> p;
			fin >> I;
			fin >> p;
			d(I);
		}
		if (next == 's') {
			char I;
			char p;
			fin >> p;
			fin >> I;
			fin >> p;
			s(I, fout);
		}
	}
}