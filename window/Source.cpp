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
	char c;
	int x1;
	int y1;
	int x2;
	int y2;
	window(char c, int x, int y, int X, int Y) {
		this->c = c;
		this->x1 = x;
		this->y1 = y;
		this->x2 = X;
		this->y2 = Y;
	}
};

vector<window> wins;

void w(char I, int x, int y, int X, int Y) {
	if (x > X) {
		int t = x;
		x = X;
		X = t;
	}
	if (y > Y) {
		int t = y;
		y = Y;
		Y = t;
	}
	window w(I, x, y, X, Y);
	wins.push_back(w);
}

void t(char I) {
	for (int i = 0; i < wins.size(); i++) {
		if (wins[i].c == I) {
			wins.push_back(wins[i]);
			wins.erase(wins.begin() + i);
			break;
		}
	}
}

void b(char I) {
	for (int i = 0; i < wins.size(); i++) {
		if (wins[i].c == I) {
			wins.insert(wins.begin(), wins[i]);
			wins.erase(wins.begin() + i + 1);
			break;
		}
	}
}

void d(char I) {
	for (int i = 0; i < wins.size(); i++) {
		if (wins[i].c == I) {
			wins.erase(wins.begin() + i);
			break;
		}
	}
}

bool isProperWindow(window& w) {
	return w.x1 < w.x2&& w.y1 < w.y2;
}

vector<window> calc(window& w, window b) {
	vector<window> list;
	if (b.x1 < w.x1) {
		b.x1 = w.x1;
	}
	if (b.y1 < w.y1) {
		b.y1 = w.y1;
	}
	if (b.x2 > w.x2) {
		b.x2 = w.x2;
	}
	if (b.y2 > w.y2) {
		b.y2 = w.y2;
	}
	if (b.x1 >= b.x2 || b.y1 >= b.y2) {
		list.push_back(w);
		return list;
	}

	window w1(0, w.x1, w.y1, w.x2, b.y1);
	window w2(0, w.x1, b.y2, w.x2, w.y2);
	window w3(0, w.x1, b.y1, b.x1, b.y2);
	window w4(0, b.x2, b.y1, w.x2, b.y2);

	if (isProperWindow(w1)) {
		list.push_back(w1);
	}
	if (isProperWindow(w2)) {
		list.push_back(w2);
	}
	if (isProperWindow(w3)) {
		list.push_back(w3);
	}
	if (isProperWindow(w4)) {
		list.push_back(w4);
	}
	return list;
}


float s(char I) {
	bool above = false;
	vector<window> list;
	float total = 0;
	for (int i = 0; i < wins.size(); i++) {
		if (wins[i].c == I) {
			above = true;
			list.push_back(wins[i]);
			total = (wins[i].x2 - wins[i].x1) * (wins[i].y2 - wins[i].y1);
			continue;
		}
		if (!above) {
			continue;
		}
		vector<window> newList;
		for (int j = 0; j < list.size(); j++) {
			 vector<window> subwins = calc(list[j], wins[i]);
			 for (int k = 0; k < subwins.size(); k++) {
				 newList.push_back(subwins[k]);
			 }
		}
		list = newList;
	}

	float totalVisible = 0;
	for (int i = 0; i < list.size(); i++) {
		totalVisible += (list[i].x2 - list[i].x1) * (list[i].y2 - list[i].y1);
	}

	float ratio = totalVisible / total;
	float percentage = ratio * 100;
	return percentage;
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
			fprintf(fout, "%.3f\n", s(I));
		}
	}
}