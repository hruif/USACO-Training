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
	Square(int r, int col) {
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

vector<vector<int>> masterBoard;
// Board keeping track of the total of every knight's distance from a square

vector<vector<bool>> kingUp;
// Keeps track of if any of the shortest path for all knights to a square involves a knight picking up the king

/*
vector<vector<vector<bool>>> knightKingUp;
*/
// Keeps track of kingUp but for each individual knight

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


int abs(int a) noexcept{
	if (a < 0) {
		a = -a;
	}
	return a;
}
// Absolute value function


int kingMovesTo(Square a) {
	int val = abs(a.column - king.column);
	int rows = abs(a.row - king.row);
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


void moveKnight(vector<vector<int>>& board, vector<vector<bool>>& knightKingUp, queue<Square>& nextSquares, queue<int>& moves, queue<bool>& kingState){
	/*
	Square knight - the current square the knight is on
	int knightIndex - index of the knight in arrays
	int moves - how many moves it has taken the knight to get to this square
	vector<vector<int>>& board - a board to keep track of the knight's distance from every square
	bool kingPicked - the king's state (picked up or not)
	vector<vector<bool>> knightKingUp - if the king has been picked up on the path to a square by this knight

	vector<Square>& path - path the knight has taken to get to this square - DELETED
	*/
	Square knight = nextSquares.front();
	bool kingPicked = kingState.front();
	int onMove = moves.front();
	if (!kingPicked) {
		if (onKing(knight)) {
			kingPicked = true;
		}
	}
	// If the knight on the same square as the king, show it as picked up

	int row = knight.row;
	int col = knight.column;
	int found = board[col][row];
	if (found < onMove && found != -1) {
		nextSquares.pop();
		moves.pop();
		kingState.pop();
		return;
	}
	if (found == onMove) {
		if (knightKingUp[col][row] || !kingPicked) {
			nextSquares.pop();
			moves.pop();
			kingState.pop();
			return;
		}
	}
	// If a same distance path has been found, and the state of the king is the same, return

	board[col][row] = onMove;
	knightKingUp[col][row] = kingPicked;
	// Update all paths, the board, and the king's state

	Square next(0, 0);
	for (int i = -2; i <= 2; i++) {
		if (i == 0) {
			continue;
		}
		// Knight cannot move to same row or column

		for (int j = -2; j <= 2; j++) {
			if (abs(i) == abs(j) || j == 0) {
				continue;
			}
			// Knight cannot move diagonally
			int nextCol = col + i;
			int nextRow = row + j;
			next.setVals(nextCol, nextRow);
				if (isRealSquare(next)) {
					nextSquares.push(next);
					moves.push(onMove + 1);
					kingState.push(kingPicked);
				}
			// Moves knight to a square
		}
	}
	nextSquares.pop();
	moves.pop();
	kingState.pop();
}
// Moves a knight to every possible square


void solve() {
	for (int i = 0; i < knights.size(); i++) {
	// Runs through every knight

		vector<Square> path;
		// Paths array for the knight

		vector<vector<int>> board(C, vector<int>(R, -1));
		// Board array for the knight

		vector<vector<bool>> knightKingUp(C, vector<bool>(R, false));
		// Keeps track of if this knight has picked up king on a path to a square

		queue<Square> nextSquare;
		queue<int> moves;
		queue<bool> kingState;
		nextSquare.push(knights[i]);
		moves.push(0);
		kingState.push(false);

		while (!nextSquare.empty()) {
			moveKnight(board, knightKingUp, nextSquare, moves, kingState);
		}

		for (int i = 0; i < C; i++) {
			for (int j = 0; j < R; j++) {
				masterBoard[i][j] += board[i][j];
				if (kingUp[i][j] || knightKingUp[i][j]) {
					kingUp[i][j] = true;
				}
			}
		}
		// Updates the masterBoard and kingUp arrays with what was found
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

	masterBoard.resize(C, vector<int>(R, 0));
	kingUp.resize(C, vector<bool>(R, false));

	int ans = -1;
	if (knights.size() > 0) {
		solve();
		for (int i = 0; i < masterBoard.size(); i++) {
			for (int j = 0; j < masterBoard[i].size(); j++) {
				int moves = masterBoard[i][j];
				if (moves < ans || ans == -1) {
					if (kingUp[i][j]) {
						ans = moves;
					}
				}
			}
		}
		// Only outputs answer if king was picked up - probably will prevent correct answer on some test cases
	}
	else {
		ans = kingMovesTo(king);
	}

	ofstream fout("camelot.out");
	fout << ans << '\n';
}