/*
ID: ruifanl1
TASK: wormhole
LANG: C++
*/

#include <fstream>
#include <string.h>

int N, total = 0;

struct Coordinates {
	int x;
	int y;
};

bool checkLoop(int pairs[][2], Coordinates* wormholes) {
	int m = N / 2 - 1;
	for (int x = 0; x <= m; x++) {
		for (int i = 0; i < 2; i++) {
			int cow = pairs[x][i];
			int cowPair = x;
			while (true) {
				int nextWormhole = -1;
				int outWormhole = -1;
				int outWormholePair = -1;
				for (int j = 0; j <= m; j++) {
					for (int k = 0; k < 2; k++) {
						int a = pairs[j][k];
						if (wormholes[cow].y == wormholes[a].y && wormholes[a].x > wormholes[cow].x) {
							if (nextWormhole == -1) {
								nextWormhole = a;
								outWormhole = pairs[j][1 - k];
								outWormholePair = j;
							}
							else if (wormholes[nextWormhole].x > wormholes[a].x) {
								nextWormhole = a;
								outWormhole = pairs[j][1 - k];
								outWormholePair = j;
							}
						}
					}
				}
				if (nextWormhole == -1) {
					break;
				}
				cow = outWormhole;
				cowPair = outWormholePair;
				if (cow == pairs[x][i]) {
					return true;
				}
			}
		}
	}
	return false;
}

void printPairing(int pairs[][2], int n) {
	for (int i = 0; i < n; i++) {
		printf("(%2d, %2d) ", pairs[i][0], pairs[i][1]);
	}
	printf("\n");
}

void findHole(bool* wormholesStatus, Coordinates* wormholes, int pairs[][2], int pairNum, int index) {
	int startPos = 1;
	if (index == 1) {
		startPos = pairs[pairNum][0] + 1;
	}
	else {
		startPos = pairs[pairNum - 1][0] + 1;
	}
	for (int i = startPos; i < N; i++) {
		if (wormholesStatus[i]) {
			continue;
		}
		wormholesStatus[i] = true;
		pairs[pairNum][index] = i;
		int nextPairNum = index == 1 ? pairNum + 1 : pairNum;
		int nextIndex = 1 - index;
		if (index == 1 && pairNum == N / 2 - 1 && checkLoop(pairs, wormholes)) {
			total++;
			printPairing(pairs, pairNum + 1);
		}
		else {
			if (nextPairNum < N / 2) {
				findHole(wormholesStatus, wormholes, pairs, nextPairNum, nextIndex);
			}
		}
		wormholesStatus[i] = false;
		if (index == 0) {
			break;
		}
	}
}

int main() {
	FILE* fin = fopen("wormhole.in", "r"), * fout = fopen("wormhole.out", "w");
	fscanf(fin, "%d", &N);
	Coordinates wormholes[12];
	int pairs[6][2];
	bool wormholeStatus[12];
	memset(wormholeStatus, 0, 12);
	for (int i = 0; i < N; i++) {
		fscanf(fin, "%d %d", &wormholes[i].x, &wormholes[i].y);
	}

	wormholeStatus[0] = true;
	pairs[0][0] = 0;
	findHole(wormholeStatus, wormholes, pairs, 0, 1);

	fprintf(fout, "%d\n", total);
}