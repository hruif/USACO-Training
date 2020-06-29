/*
ID: ruifanl1
TASK: camelot
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int R, C;

struct Square
{
	int row;
	int column;
	Square(int col, int r) {
		row = r;
		column = col;
	}
	void setVals(int col, int r) {
		row = r;
		column = col;
	}
	void coordToBoard(char colLetter, int r) {
		row = r - 1;
		column = colLetter - 'A';
	}
	// Input board coordinates (letter, number) and convert to pointers for program

};
// Square struct to show a square on the board


Square king(0, 0);
// King's starting square

vector<Square> knights;
// Starting squares of all knights

vector<vector<vector<vector<int>>>> allDists;
// Board keeping track of the total of every knight's distance from a square

vector<vector<bool>> kingUp;
// Keeps track of if any of the shortest path for all knights to a square involves a knight picking up the king

vector<vector<int>> kingDists;

vector<vector<vector<vector<Square>>>> allPaths;
// Keeps track of shortest path for every knight to every square


bool isRealSquare(Square square) {
	if (square.row < 0 || square.column < 0) {
		return false;
	}
	if (square.row >= R || square.column >= C) {
		return false;
	}
	return true;
}
// Verifies the square inputted is on the board


int absolute(int a) noexcept {
	if (a < 0) {
		a = -a;
	}
	return a;
}
// Absolute value function


int kingMovesTo(Square a) {
	int val = absolute(a.column - king.column);
	int rows = absolute(a.row - king.row);
	if (val < rows) {
		val = rows;
	}
	return val;
}
// Not used function to determine king's distance from a square


bool onKing(Square square) {
	if (square.column == king.column && square.row == king.row) {
		return true;
	}
	return false;
}
// Determines if the king is on a square


void moveKnight(queue<Square>& nextSquares, Square currentSquare) {
	/*
	Square knight - the current square the knight is on
	int knightIndex - index of the knight in arrays
	int moves - how many moves it has taken the knight to get to this square
	vector<vector<int>>& board - a board to keep track of the knight's distance from every square
	*/
	Square knight = nextSquares.front();
	nextSquares.pop();

	int row = knight.row;
	int col = knight.column;
	int onMove = allDists[currentSquare.column][currentSquare.row][col][row];

	Square next(col + 2, row + 1);
	if (isRealSquare(next) && allDists[currentSquare.column][currentSquare.row][next.column][next.row] == -1) {
		allDists[currentSquare.column][currentSquare.row][next.column][next.row] = onMove + 1;
		nextSquares.push(next);
	}
	next.setVals(col + 2, row - 1);
	if (isRealSquare(next) && allDists[currentSquare.column][currentSquare.row][next.column][next.row] == -1) {
		allDists[currentSquare.column][currentSquare.row][next.column][next.row] = onMove + 1;
		nextSquares.push(next);
	}
	next.setVals(col - 2, row + 1);
	if (isRealSquare(next) && allDists[currentSquare.column][currentSquare.row][next.column][next.row] == -1) {
		allDists[currentSquare.column][currentSquare.row][next.column][next.row] = onMove + 1;
		nextSquares.push(next);
	}
	next.setVals(col - 2, row - 1);
	if (isRealSquare(next) && allDists[currentSquare.column][currentSquare.row][next.column][next.row] == -1) {
		allDists[currentSquare.column][currentSquare.row][next.column][next.row] = onMove + 1;
		nextSquares.push(next);
	}
	next.setVals(col + 1, row + 2);
	if (isRealSquare(next) && allDists[currentSquare.column][currentSquare.row][next.column][next.row] == -1) {
		allDists[currentSquare.column][currentSquare.row][next.column][next.row] = onMove + 1;
		nextSquares.push(next);
	}
	next.setVals(col + 1, row - 2);
	if (isRealSquare(next) && allDists[currentSquare.column][currentSquare.row][next.column][next.row] == -1) {
		allDists[currentSquare.column][currentSquare.row][next.column][next.row] = onMove + 1;
		nextSquares.push(next);
	}
	next.setVals(col - 1, row + 2);
	if (isRealSquare(next) && allDists[currentSquare.column][currentSquare.row][next.column][next.row] == -1) {
		allDists[currentSquare.column][currentSquare.row][next.column][next.row] = onMove + 1;
		nextSquares.push(next);
	}
	next.setVals(col - 1, row - 2);
	if (isRealSquare(next) && allDists[currentSquare.column][currentSquare.row][next.column][next.row] == -1) {
		allDists[currentSquare.column][currentSquare.row][next.column][next.row] = onMove + 1;
		nextSquares.push(next);
	}
}
// Moves a knight to every possible square


void findAllDists() {
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < R; j++) {
			// Runs through every square

			vector<Square> path;
			// Paths array for the knight

			queue<Square> nextSquare;
			Square currentSquare(i, j);
 			nextSquare.push(currentSquare);
			allDists[i][j][i][j] = 0;

			while (!nextSquare.empty()) {
				moveKnight(nextSquare, currentSquare);
			}
		}
	}
}

int main() {
	ifstream fin("camelot.in");
	fin >> R >> C;
	char kingCol;
	int kingRow;
	fin >> kingCol >> kingRow;
	king.coordToBoard(kingCol, kingRow);
	// Input for king

	char col;
	while (fin.get(col)) {
		if (col == '\n' || col == ' ') {
			continue;
		}
		int row;
		fin >> row;
		Square knight(0, 0);
		knight.coordToBoard(col, row);
		knights.push_back(knight);
	}
	// Input for knights

	allDists.resize(C, vector<vector<vector<int>>>(R, vector<vector<int>>(C, vector<int>(R, -1))));
	kingUp.resize(C, vector<bool>(R, false));
	kingDists.resize(C, vector<int>(R));

	for (int i = 0; i < C; i++) {
		for (int j = 0; j < R; j++) {
			kingDists[i][j] = kingMovesTo(Square(i, j));
		}
	}

	int ans = -1;
	if (knights.size() > 0) {
		findAllDists();

		for (int gatherCol = 0; gatherCol < C; gatherCol++) {
			for (int gatherRow = 0; gatherRow < R; gatherRow++) {
				int knightMoves = 0;
				bool badSquare = false;
				for (int k = 0; k < knights.size(); k++) {
					Square knight = knights[k];
					int dist = allDists[knight.column][knight.row][gatherCol][gatherRow];
					if (dist == -1) {
						badSquare = true;
						break;
					}
					knightMoves += dist;
				}
				if (badSquare) {
					continue;
				}
				if (ans != -1 && ans < knightMoves) {
					continue;
				}

				for (int k = 0; k < knights.size(); k++) {
					int kCol = knights[k].column;
					int kRow = knights[k].row;
					for (int meetCol = 0; meetCol < C; meetCol++) {
						for (int meetRow = 0; meetRow < R; meetRow++) {
							int knightToMeet = allDists[kCol][kRow][meetCol][meetRow];
							int meetToGather = allDists[meetCol][meetRow][gatherCol][gatherRow];
							if (knightToMeet == -1 || meetToGather == -1) {
								continue;
							}
							int totalMoves = knightMoves - allDists[kCol][kRow][gatherCol][gatherRow];
							totalMoves += kingDists[meetCol][meetRow] + knightToMeet + meetToGather;
							if (totalMoves < ans || ans == -1) {
								ans = totalMoves;
							}
						}
					}
				}
			}
		}
	}
	else {
		ans = 0;
	}

	ofstream fout("camelot.out");
	fout << ans << '\n';
}