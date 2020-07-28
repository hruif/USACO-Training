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
	vector<int> directlyAbove;
	vector<int> directlyBelow;
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

void w(char I, int x, int y, int X, int Y) {
	window next(x, y, X, Y);
	int index;
	if (I <= 9) {
		index = I;
	}
	else if (I <= 'z') {
		index = I - 'a' + 10;
	}
	else {
		index = I - 'A' + 36;
	}
	windows[index] = next;
	for (int i = 0; i < 62; i++) {
		isAbove[index][i] = true;
		if (placed[i]) {
			isBelow[i][index] = true;
			allAbove[i].push_back(index);
			allBelow[index].push_back(i);
		}
	}
	placed[index] = true;
}

void t(char I) {
	int index;
	if (I <= 9) {
		index = I;
	}
	else if (I <= 'z') {
		index = I - 'a' + 10;
	}
	else {
		index = I - 'A' + 36;
	}

	for (int i = 0; i < 62; i++) {
		isAbove[index][i] = true;
		if (placed[i] && !isBelow[i][index]) {
			isBelow[i][index] = true;
			allBelow[index].push_back(i);
			allAbove[i].push_back(index);
		}
	}
	for (int i = 0; i < allAbove[index].size(); i++) {
		int next = allAbove[index][i];
		isAbove[next][index] = false;
		for (int j = 0; j < allBelow[next].size(); j++) {
			if (allBelow[next][j] == index) {
				allBelow.erase(allBelow.begin() + j);
				break;
			}
		}
	}
	allAbove[index].clear();
}

void b(char I) {
	int index;
	if (I <= 9) {
		index = I;
	}
	else if (I <= 'z') {
		index = I - 'a' + 10;
	}
	else {
		index = I - 'A' + 36;
	}

	for (int i = 0; i < 62; i++) {
		isBelow[index][i] = true;
		if (placed[i] && !isAbove[i][index]) {
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
				allAbove.erase(allAbove.begin() + j);
				break;
			}
		}
	}
	allBelow[index].clear();
}

void d(char I) {
	int index;
	if (I <= 9) {
		index = I;
	}
	else if (I <= 'z') {
		index = I - 'a' + 10;
	}
	else {
		index = I - 'A' + 36;
	}

	for (int i = 0; i < allAbove[index].size(); i++) {
		int next = allAbove[index][i];
		isAbove[next][index] = false;
		for (int j = 0; j < allBelow[next].size(); j++) {
			if (allBelow[next][j] == index) {
				allBelow.erase(allBelow.begin() + j);
				break;
			}
		}
	}
	allAbove[index].clear();
	for (int i = 0; i < allBelow.size(); i++) {
		int next = allBelow[index][i];
		isBelow[next][index] = false;
		for (int j = 0; j < allAbove[next].size(); j++) {
			if (allAbove[next][j] == index) {
				allAbove.erase(allAbove.begin() + j);
				break;
			}
		}
	}
	allBelow[index].clear();
}

void s(char I, FILE*& fout) {
	int index;
	if (I <= 9) {
		index = I;
	}
	else if (I <= 'z') {
		index = I - 'a' + 10;
	}
	else {
		index = I - 'A' + 36;
	}
	int left = windows[index].x;
	int right = windows[index].X;
	if (left > right) {
		int tmp = left;
		left = right;
		right = left;
	}
	int top = windows[index].y + 1;
	int bottom = windows[index].Y;
	if (top > bottom) {
		int tmp = top;
		top = bottom;
		bottom = tmp;
	}
	int w = right - left + 1;
	int h = bottom - top + 1;
	vector<vector<bool>> covered(w, vector<bool>(h, false));

	for (int i = 0; i < allAbove[index].size(); i++) {
		int next = allAbove[index][i];
		int nextL = windows[next].x;
		int nextR = windows[next].X;
		int nextT = windows[next].y;
		int nextB = windows[next].Y;
		if (nextB < nextT) {
			int tmp = nextB;
			nextB = nextT;
			nextT = tmp;
		}
		if (nextL > nextR) {
			int tmp = nextL;
			nextL = nextR;
			nextR = tmp;
		}
		if (nextL > right) {
			continue;
		}
		if (nextL < left) {
			nextL = left;
		}
		if (nextR < left) {
			continue;
		}
		if (nextR > right) {
			nextR = right;
		}
		if (nextT > bottom) {
			continue;
		}
		if (nextT < top) {
			nextT = top;
		}
		if (nextB < top) {
			continue;
		}
		if (nextB > bottom) {
			nextB = bottom;
		}
		for (int j = nextL; j <= nextR; j++) {
			for (int k = nextT; k <= nextB; k++) {
				covered[j - left][k - top] = true;
			}
		}
	}

	float numCovered = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (covered[i][j]) {
				numCovered++;
			}
		}
	}
	float total = w * h;
	if (numCovered == 0) {
		fprintf(fout, "%.3f\n", 100.000);
	}
	else {
		numCovered *= 100;
		float percentage = 100 - numCovered / total;
		fprintf(fout, "%.3f\n", percentage);
	}
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