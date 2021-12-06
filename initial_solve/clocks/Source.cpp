/*
ID: ruifanl1
TASK: clocks
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>

using namespace std;

int clocks[9];
int moves[36];
int ansMoves[36];
int totalMoves = 36;
bool cache[500000];
bool found = false;

long long aaa;

int clocksToInt() {
	int b = 1;
	int val = 0;
	for (int i = 0; i < 9; i++) {
		int c = clocks[i];
		int v;
		if (c == 12) {
			v = 0;
		}
		else if (c == 3) {
			v = 1;
		}
		else if (c == 6) {
			v = 2;
		}
		else {
			v = 3;
		}
		val += v * b;
		b <<= 2;
	}
	return val;
}

int cB(int pos) {
	if (pos == 0) {
		pos = 12;
	}
	if (pos == 15) {
		pos = 3;
	}
	return pos;
}

void move1(bool reverse) { // ABDE - 0134
	int change = reverse ? -3 : 3;
	clocks[0] = cB(clocks[0] + change);
	clocks[1] = cB(clocks[1] + change);
	clocks[3] = cB(clocks[3] + change);
	clocks[4] = cB(clocks[4] + change);
}

void move2(bool reverse) { // ABC - 012
	int change = reverse ? -3 : 3;
	clocks[0] = cB(clocks[0] + change);
	clocks[1] = cB(clocks[1] + change);
	clocks[2] = cB(clocks[2] + change);
}

void move3(bool reverse) { // BCEF - 1245
	int change = reverse ? -3 : 3;
	clocks[1] = cB(clocks[1] + change);
	clocks[2] = cB(clocks[2] + change);
	clocks[4] = cB(clocks[4] + change);
	clocks[5] = cB(clocks[5] + change);
}

void move4(bool reverse) { // ADG - 036
	int change = reverse ? -3 : 3;
	clocks[0] = cB(clocks[0] + change);
	clocks[3] = cB(clocks[3] + change);
	clocks[6] = cB(clocks[6] + change);
}

void move5(bool reverse) { // BDEFH - 13457
	int change = reverse ? -3 : 3;
	clocks[1] = cB(clocks[1] + change);
	clocks[3] = cB(clocks[3] + change);
	clocks[4] = cB(clocks[4] + change);
	clocks[5] = cB(clocks[5] + change);
	clocks[7] = cB(clocks[7] + change);
}

void move6(bool reverse) { // CFI - 258
	int change = reverse ? -3 : 3;
	clocks[2] = cB(clocks[2] + change);
	clocks[5] = cB(clocks[5] + change);
	clocks[8] = cB(clocks[8] + change);
}

void move7(bool reverse) { // DEGH - 3467
	int change = reverse ? -3 : 3;
	clocks[3] = cB(clocks[3] + change);
	clocks[4] = cB(clocks[4] + change);
	clocks[6] = cB(clocks[6] + change);
	clocks[7] = cB(clocks[7] + change);
}

void move8(bool reverse) { // GHI - 678
	int change = reverse ? -3 : 3;
	clocks[6] = cB(clocks[6] + change);
	clocks[7] = cB(clocks[7] + change);
	clocks[8] = cB(clocks[8] + change);
}

void move9(bool reverse) { // EFHI - 4578
	int change = reverse ? -3 : 3;
	clocks[4] = cB(clocks[4] + change);
	clocks[5] = cB(clocks[5] + change);
	clocks[7] = cB(clocks[7] + change);
	clocks[8] = cB(clocks[8] + change);
}

bool checkAns() {
	for (int i = 0; i < 9; i++) {
		assert(i < 9);
		if (clocks[i] != 12) {
			return false;
		}
	}
	return true;
}

bool nextStep(int m, int* moved, int last) {
	if (m >= totalMoves) {
		return false;
	}
	if (checkAns()) {
		totalMoves = m;
		for (int i = 0; i < m; i++) {
			ansMoves[i] = moves[i];
		}
		return true;
	}
	int cVal = clocksToInt();
	if (cache[cVal]) {
		return false;
	}
	cache[cVal] = true;

	bool ans = false;

	if (moved[0] < 4 && last <= 0) {
		move1(false);
		moved[0]++;
		moves[m] = 0;
		if (nextStep(m + 1, moved, 0)) {
			ans = true;
		}
		moved[0]--;
		move1(true);
	}

	if (moved[1] < 4 && last <= 1) {
		move2(false);
		moved[1]++;
		moves[m] = 1;
		if (nextStep(m + 1, moved, 1)) {
			ans = true;
		}
		moved[1]--;
		move2(true);
	}

	if (moved[2] < 4 && last <= 2) {
		move3(false);
		moved[2]++;
		moves[m] = 2;
		if (nextStep(m + 1, moved, 2)) {
			ans = true;
		}
		moved[2]--;
		move3(true);
	}

	if (moved[3] < 4 && last <= 3) {
		move4(false);
		moved[3]++;
		moves[m] = 3;
		if (nextStep(m + 1, moved, 3)) {
			ans = true;
		}
		moved[3]--;
		move4(true);
	}

	if (moved[4] < 4 && last <= 4) {
		move5(false);
		moved[4]++;
		moves[m] = 4;
		if (nextStep(m + 1, moved, 4)) {
			ans = true;
		}
		moved[4]--;
		move5(true);
	}

	if (moved[5] < 4 && last <= 5) {
		move6(false);
		moved[5]++;
		moves[m] = 5;
		if (nextStep(m + 1, moved, 5)) {
			ans = true;
		}
		moved[5]--;
		move6(true);
	}

	if (moved[6] < 4 && last <= 6) {
		move7(false);
		moved[6]++;
		moves[m] = 6;
		if (nextStep(m + 1, moved, 6)) {
			ans = true;
		}
		moved[6]--;
		move7(true);
	}

	if (moved[7] < 4 && last <= 7) {
		move8(false);
		moved[7]++;
		moves[m] = 7;
		if (nextStep(m + 1, moved, 7)) {
			ans = true;
		}
		moved[7]--;
		move8(true);
	}

	if (moved[8] < 4 && last <= 8) {
		move9(false);
		moved[8]++;
		moves[m] = 8;
		if (nextStep(m + 1, moved, 8)) {
			ans = true;
		}
		moved[8]--;
		move9(true);
	}
	if (ans) {
		cache[cVal] = false;
		return true;
	}
	return false;
}

void solve() {
	int moved[9];
	for (int i = 0; i < 9; i++) {
		moved[i] = 0;
	}
	nextStep(0, moved, -1);
}

void moveClocks(int move_num) {
	switch (move_num) {
	case 0:
		move1(false);
		break;
	case 1:
		move2(false);
		break;
	case 2:
		move3(false);
		break;
	case 3:
		move4(false);
		break;
	case 4:
		move5(false);
		break;
	case 5:
		move6(false);
		break;
	case 6:
		move7(false);
		break;
	case 7:
		move8(false);
		break;
	case 8:
		move9(false);
		break;
	}
}

void dfs(int move_num, int num_of_moves) {
	if (num_of_moves >= totalMoves) {
		return;
	}

	if (move_num == 9) {
		if (checkAns()) {
			totalMoves = num_of_moves;
			for (int i = 0; i < num_of_moves; i++) {
				ansMoves[i] = moves[i];
			}
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (i > 0) {
			moveClocks(move_num);
			moves[num_of_moves++] = move_num;
		}
		dfs(move_num + 1, num_of_moves);
	}
	moveClocks(move_num);
}

int main() {
	ifstream fin("clocks.in");
	for (int i = 0; i < 9; i++) {
		int clock;
		fin >> clock;
		clocks[i] = clock;
	}

	dfs(0, 0);

	ofstream fout("clocks.out");
	for (int i = 0; i < totalMoves; i++) {
		if (i != 0) {
			fout << ' ';
		}
		fout << ansMoves[i] + 1;
	}
	fout << '\n';
}