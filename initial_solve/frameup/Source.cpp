/*
ID: ruifanl1
TASK: frameup
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int H, W, N;
vector<char> letters;
vector<bool> usedLetters(26, false);
vector<vector<char>> board;
vector<vector<int>> coveredBy(27), covering(27);
vector<vector<bool>> canPickNext;

void findRect(vector<int>& rect, char rectLetter) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (board[i][j] == rectLetter) {
				if (i < rect[0] || rect[0] == -1) {
					rect[0] = i;
				}
				if (i > rect[1]) {
					rect[1] = i;
				}
				if (j < rect[2] || rect[2] == -1) {
					rect[2] = j;
				}
				if (j > rect[3]) {
					rect[3] = j;
				}
			}
		}
	}
	rect[4] = rectLetter - 'A';
}

void findCovering(vector<int>& rect) {
	if (rect.size() == 0) {
		return;
	}
	int rectIndex = rect[4];
	int w = rect[3] - rect[2] + 1;
	int h = rect[1] - rect[0] + 1;
	vector<bool> checked(26, false);
	checked[rect[4]] = true;
	for (int i = 0; i < w; i++) {
		int column = rect[2] + i;
		int topIndex = board[rect[0]][column] - 'A';
		if (!checked[topIndex]) {
			coveredBy[rectIndex].push_back(topIndex);
			covering[topIndex].push_back(rectIndex);
			checked[topIndex] = true;
		}

		int botIndex = board[rect[1]][column] - 'A';
		if (!checked[botIndex]) {
			coveredBy[rectIndex].push_back(botIndex);
			covering[botIndex].push_back(rectIndex);
			checked[botIndex] = true;
		}
	}
	for (int i = 0; i < h; i++) {
		int row = rect[0] + i;
		int leftIndex = board[row][rect[2]] - 'A';
		if (!checked[leftIndex]) {
			coveredBy[rectIndex].push_back(leftIndex);
			covering[leftIndex].push_back(rectIndex);
			checked[leftIndex] = true;
		}

		int rightIndex = board[row][rect[3]] - 'A';
		if (!checked[rightIndex]) {
			coveredBy[rectIndex].push_back(rightIndex);
			covering[rightIndex].push_back(rectIndex);
			checked[rightIndex] = true;
		}
	}
	coveredBy[rectIndex].push_back(26);
}

void findIllegals(int source, int current, vector<bool>& legal) {
	if (coveredBy[current].size() == 0) {
		return;
	}
	for (int i = 0; i < coveredBy[current].size(); i++) {
		if (legal[coveredBy[current][i]]) {
			legal[coveredBy[current][i]] = false;
			findIllegals(source, coveredBy[current][i], legal);
		}
	}
}

bool checkCanVisit(int index, vector<bool>& visited) {
	if (index == 26) {
		return true;
	}
	if (!usedLetters[index]) {
		return false;
	}
	if (covering[index].size() == 0) {
		return true;
	}
	for (int i = 0; i < covering[index].size(); i++) {
		if (!visited[covering[index][i]]) {
			return false;
		}
	}
	return true;
}

void outputAll(ofstream& fout, vector<bool>& canVisit, vector<bool>& visited, vector<int>& output) {
	if (output.size() == N) {
		for (int i = 0; i < output.size(); i++) {
			char letter = output[i] + 'A';
			fout << letter;
		}
		fout << '\n';
	}
	for (int i = 0; i < 26; i++) {
		if (visited[i]) {
			continue;
		}
		if (canVisit[i]) {
			vector<int> changed;
			visited[i] = true;
			output.push_back(i);
			for (int j = 0; j < 27; j++) {
				if (!canPickNext[i][j]) {
					continue;
				}
				if (!canVisit[j] && checkCanVisit(j, visited)) {
					changed.push_back(j);
					canVisit[j] = true;
				}
			}
			outputAll(fout, canVisit, visited, output);
			for (int j = 0; j < changed.size(); j++) {
				canVisit[changed[j]] = false;
			}
			visited[i] = false;
			output.pop_back();
		}
	}
}

int main() {
	ifstream fin("frameup.in");

	fin >> H >> W;
	for (int i = 0; i < H; i++) {
		vector<char> row; 
		for (int j = 0; j < W; j++) {
			char tmp;
			fin >> tmp;
			if (tmp != '.') {
				if (!usedLetters[tmp - 'A']) {
					N++;
					usedLetters[tmp - 'A'] = true;
				}
			}
			row.push_back(tmp);
		}
		board.push_back(row);
	}

	for (int i = 0; i < 26; i++) {
		if (usedLetters[i]) {
			letters.push_back(i + 'A');
		}
	}
	vector<vector<int>> allRects(letters.size());
	for (int i = 0; i < letters.size(); i++) {
		vector<int> rect(5, -1); // up, down, left, right, letter - 'A'
		findRect(rect, letters[i]);
		allRects[i] = rect;
	}

	for (int i = 0; i < letters.size(); i++) {
		findCovering(allRects[i]);
	}

	vector<int> possibleBottoms;
	for (int i = 0; i < 26; i++) {
		if (covering[i].size() == 0 && usedLetters[i]) {
			possibleBottoms.push_back(i);
		}
	}

	for (int i = 0; i < 26; i++) {
		vector<bool> isLegal(27, true);
		for (int j = 0; j < coveredBy[i].size(); j++) {
			findIllegals(i, coveredBy[i][j], isLegal);
		}
		canPickNext.push_back(isLegal);
	}

	ofstream fout("frameup.out");
	for (int i = 0; i < possibleBottoms.size(); i++) {
		vector<bool> visited(27, false);
		vector<bool> canVisit(27, false);
		vector<int> output;
		canVisit[possibleBottoms[i]] = true;
		outputAll(fout, canVisit, visited, output);
	}
}