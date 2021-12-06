/*
ID: ruifanl1
TASK: twofive
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

char let;
bool found = false;
int M;
char grid[5][5];
char endState[5][5];
vector<vector<vector<int>>> choices;

void setChoices() {
	choices.resize(5, vector<vector<int>>(5));
	choices[0][0].push_back(0);
	for (int i = 1; i <= 5; i++) { // B - F
		choices[0][1].push_back(i);
		choices[1][0].push_back(i);
	}
	for (int i = 2; i <= 10; i++) { // C - K
		choices[0][2].push_back(i);
		choices[2][0].push_back(i);
	}
	for (int i = 3; i <= 9; i++) { // D - J
		choices[1][1].push_back(i);
	}
	for (int i = 3; i <= 15; i++) { // D - P
		choices[0][3].push_back(i);
		choices[3][0].push_back(i);
	}
	for (int i = 5; i <= 13; i++) { // F - N
		choices[1][2].push_back(i);
		choices[2][1].push_back(i);
	}
	for (int i = 4; i <= 20; i++) { // E - U
		choices[0][4].push_back(i);
		choices[4][0].push_back(i);
	}
	for (int i = 7; i <= 17; i++) { // H - R
		choices[1][3].push_back(i);
		choices[3][1].push_back(i);
	}
	for (int i = 8; i <= 16; i++) { // I - Q
		choices[2][2].push_back(i);
	}
	for (int i = 9; i <= 21; i++) { // J - V
		choices[1][4].push_back(i);
		choices[4][1].push_back(i);
	}
	for (int i = 11; i <= 19; i++) { // L - T
		choices[2][3].push_back(i);
		choices[3][2].push_back(i);
	}
	for (int i = 14; i <= 22; i++) { // O - W
		choices[2][4].push_back(i);
		choices[4][2].push_back(i);
	}
	for (int i = 15; i <= 21; i++) { // P - V
		choices[3][3].push_back(i);
	}
	for (int i = 19; i <= 23; i++) { // T - X
		choices[3][4].push_back(i);
		choices[4][3].push_back(i);
	}
	choices[4][4].push_back(24);
}

bool foundAns(int num) {
	if (let == 'N') {
		if (num == M) {
			return true;
		}
		return false;
	}
	else {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (grid[i][j] != endState[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
}

bool canPlace(int x, int y, int letter) {
	bool top = false, left = false;
	if (x == 0) {
		top = true;
	}
	else {
		top = grid[x - 1][y] < letter + 'A';
	}
	if (y == 0) {
		left = true;
	}
	else {
		left = grid[x][y - 1] < letter + 'A';
	}
	return top && left;
}

void changeVal(int& count, int x, int y, vector<bool>& visited) {
	if (y == 5) {
		x++;
		y = 0;
	}
	if (x == 4 && y == 4) {
		grid[x][y] = 'Y';
		count++;
		if (foundAns(count)) {
			found = true;
		}
		return;
	}
	for (int i = 0; i < 24; i++) {
		if (!visited[i] && canPlace(x, y, i)) {
			visited[i] = true;
			grid[x][y] = i + 'A';
			changeVal(count, x, y + 1, visited);
			visited[i] = false;
			if (found) {
				return;
			}
		}
	}
}

int findAns() {
	vector<bool> visited(25, false);
	int count = 0;
	changeVal(count, 0, 0, visited);
	return count;
}

int main() {
	ifstream fin("twofive.in");
	fin >> let;
	if (let == 'N') {
		fin >> M;
	}
	else {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				fin >> endState[i][j];
			}
		}
	}

	int num = findAns();

	ofstream fout("twofive.out");
	if (let == 'W') {
		fout << num;
	}
	else {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				fout << grid[i][j];
			}
		}
	}
	fout << '\n';
}