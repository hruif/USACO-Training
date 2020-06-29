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
	void setVals(int r, int col) {
		row = r;
		column = col;
	}
	void coordToBoard(char rowLetter, int col) {
		row = rowLetter - 'A';
		column = col - 1;
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
	if (square.row < 0 || square.row >= R) {
		return false;
	}
	if (square.column < 0 || square.column >= C) {
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


void moveKnight(Square knight, int knightIndex, int moves, vector<vector<int>>& board, bool kingPicked, vector<vector<bool>>& knightKingUp){
	/*
	Square knight - the current square the knight is on
	int knightIndex - index of the knight in arrays
	int moves - how many moves it has taken the knight to get to this square
	vector<vector<int>>& board - a board to keep track of the knight's distance from every square
	bool kingPicked - the king's state (picked up or not)
	vector<vector<bool>> knightKingUp - if the king has been picked up on the path to a square by this knight

	vector<Square>& path - path the knight has taken to get to this square - DELETED
	*/

	int row = knight.row;
	int col = knight.column;
	int found = board[col][row];

	/*
	path.push_back(knight);
	*/

	// Adds current square to path for the knight

	if (found != -1 && found < moves) {

		/*
		path.pop_back();
		*/

		return;
	}
	// If a shorter path has already been found to this square, return

	if (onKing(knight)) {
		kingPicked = true;
	}
	// If the knight on the same square as the king, show it as picked up

	if (found == moves) {
		if (knightKingUp[col][row] || !kingPicked) {
			
			/*
			path.pop_back();
			*/

			return;
		}
	}
	// If a same distance path has been found, and the state of the king is the same, return

	board[col][row] = moves;

	/*
	allPaths[knightIndex][col][row] = path;
	*/

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
			next.setVals(col + i, row + j);
			if (isRealSquare(next)) {
				moveKnight(next, knightIndex, moves + 1, board, kingPicked, knightKingUp);
			}
			// Moves knight to a square
		}
	}

	/*
	path.pop_back();
	*/

	// Removes last square from path because the array is shared

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

		moveKnight(knights[i], i, 0, board, false, knightKingUp);
		// Finds paths and distances to all squares

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
	
	/*
	allPaths.resize(knights.size(), vector<vector<vector<Square>>>(C, vector<vector<Square>>(R)));
	*/

	int ans = -1;
	if (knights.size() > 0) {
		solve();

		/*
		for (int i = 0; i < C; i++) {
			for (int j = 0; j < R; j++) {
				for (int k = 0; k < knights.size(); k++) {
					if (knightKingUp[k][i][j]) {
						kingUp[i][j] = true;
						break;
					}
				}
			}
		}
		// Moves king states from knightKingUp to kingUp so it is easier to search for the states
		*/

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