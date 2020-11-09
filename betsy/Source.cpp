/*
ID: ruifanl1
TASK: betsy
LANG: C++
*/

#define ll long long

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int N;
bool visited[7][7];
unordered_map<ll, ll> cache;

ll stateToll(int x, int y) {
	ll total = 0;
	ll b = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j]) {
				total += b;
			}
			b <<= 1;
		}
	}
	total += b * x;
	b <<= 3;
	total += b * y;
	return total;
}

bool canVisit(int x, int y) {
	if (x < 0 || x >= N) {
		return false;
	}
	if (y < 0 || y >= N) {
		return false;
	}
	if (visited[x][y]) {
		return false;
	}
	return true;
}

bool noTraps(int x, int y) {
	for (int i = -1; i <= 1; i += 2) {
		if (canVisit(x + i, y) && (x + i != N - 1 && y != 0)) {
			int nx = x + i;
			bool valid = false;

			for (int j = -1; j <= 1; j += 2) {
				if (canVisit(nx, y + j)) {
					valid = true;
					break;
				}
				if (canVisit(nx + j, y)) {
					valid = true;
					break;
				}
			}
			if (!valid) {
				return false;
			}
		}
		if (canVisit(x, y + i) && (x != N - 1 && y + i != 0)) {
			int ny = y + i;
			bool valid = false;

			for (int j = -1; j <= 1; j += 2) {
				if (canVisit(x, ny + j)) {
					valid = true;
					break;
				}
				if (canVisit(x + j, ny)) {
					valid = true;
					break;
				}
			}
			if (!valid) {
				return false;
			}
		}
	}
	return true;
}

int countAdjacents(int x, int y) {
	if (!canVisit(x, y)) {
		return 0;
	}

	int count = 0;
	if (canVisit(x - 1, y)) {
		count++;
	}
	if (canVisit(x + 1, y)) {
		count++;
	}
	if (canVisit(x, y - 1)) {
		count++;
	}
	if (canVisit(x, y + 1)) {
		count++;
	}
	return count;
}

bool checkRow(int x, int y1, int y2) {
	for (int i = y1; i < y2; i++) {
		if (!visited[x][i]) {
			return false;
		}
	}
	return true;
}

bool checkCol(int x1, int x2, int y) {
	for (int i = x1; i < x2; i++) {
		if (!visited[i][y]) {
			return false;
		}
	}
	return true;
}

ll findSols(int x, int y) {
	if (x == 0) {
		if (!checkRow(x, 0, y)) {
			return 0;
		}
	}
	if (y == N - 1) {
		if (!checkRow(0, 0, N)) {
			return 0;
		}
		if (!checkCol(0, x, y)) {
			return 0;
		}
	}
	if (x == N - 1) {
		if (!checkRow(x, y + 1, N)) {
			return 0;
		}
		if (!checkCol(0, N, N - 1)) {
			return 0;
		}
	}

	if (x == N - 1 && y == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visited[i][j]) {
					return 0;
				}
			}
		}
		return 1;
	}

	ll state = stateToll(x, y);

	if (cache.find(state) != cache.end()) {
		return cache[state];
	}

	ll total = 0;

	int right = countAdjacents(x, y + 1);
	int left = countAdjacents(x, y - 1);
	int up = countAdjacents(x - 1, y);
	int down = countAdjacents(x + 1, y);

	int n = 0;
	bool nUp, nDown, nRight, nLeft;
	nUp = nDown = nRight = nLeft = false;
	if (right == 1) {
		nRight = true;
		n++;
	}
	if (left == 1 && !(x == N - 1 && y - 1 == 0)) {
		nLeft = true;
		n++;
	}
	if (up == 1) {
		nUp = true;
		n++;
	}
	if (down == 1 && !(x + 1 == N - 1 && y == 0)) {
		nDown = true;
		n++;
	}

	if (n > 1) {
		return 0;
	}
	else if (n == 1) {
		if (nUp && canVisit(x - 1, y)) {
			visited[x - 1][y] = true;
			if (noTraps(x - 1, y)) {
				total += findSols(x - 1, y);
			}
			visited[x - 1][y] = false;
		}
		if (nRight && canVisit(x, y + 1)) {
			visited[x][y + 1] = true;
			if (noTraps(x, y + 1)) {
				total += findSols(x, y + 1);
			}
			visited[x][y + 1] = false;
		}
		if (nDown && canVisit(x + 1, y)) {
			visited[x + 1][y] = true;
			if (noTraps(x + 1, y)) {
				total += findSols(x + 1, y);
			}
			visited[x + 1][y] = false;
		}
		if (nLeft && canVisit(x, y - 1)) {
			visited[x][y - 1] = true;
			if (noTraps(x, y - 1)) {
				total += findSols(x, y - 1);
			}
			visited[x][y - 1] = false;
		}
		return total;
	}

	if (canVisit(x, y - 1)) {
		visited[x][y - 1] = true;
		if (noTraps(x, y - 1)) {
			total += findSols(x, y - 1);
		}
		visited[x][y - 1] = false;
	}
	if (canVisit(x, y + 1)) {
		visited[x][y + 1] = true;
		if (noTraps(x, y + 1)) {
			total += findSols(x, y + 1);
		}
		visited[x][y + 1] = false;
	}
	if (canVisit(x - 1, y)) {
		visited[x - 1][y] = true;
		if (noTraps(x - 1, y)) {
			total += findSols(x - 1, y);
		}
		visited[x - 1][y] = false;
	}
	if (canVisit(x + 1, y)) {
		visited[x + 1][y] = true;
		if (noTraps(x + 1, y)) {
			total += findSols(x + 1, y);
		}
		visited[x + 1][y] = false;
	}

	cache[state] = total;
	return total;
}

int main() {
	ifstream fin("betsy.in");
	fin >> N;

	visited[0][0] = true;
	ll ans = findSols(0, 0);

	ofstream fout("betsy.out");
	fout << ans << '\n';
}