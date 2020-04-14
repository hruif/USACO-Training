/*
ID: ruifan1
TASK: barn1
LANG: C++
*/

#include <fstream>
#include <string.h>

int addedBoards = 0, C, M;

void sort(int* array, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (array[i] > array[j]) {
				int val = array[i];
				array[i] = array[j];
				array[j] = val;
			}
		}
	}
}

void addBoard(int* toCover, bool* stalls, int* boards) {
	int maxGap = 0;
	int index = 0;
	for (int i = 0; i < C - 1; i++) {
		for (int j = 0; j < addedBoards; j++) {
			while (boards[j] == toCover[i]) {
				i++;
				j = 0;
			}
		}
		if (i >= C - 1) {
			break;
		}
		int gap = toCover[i + 1] - toCover[i];
		if (maxGap <= gap) {
			maxGap = gap;
			index = i;
		}
	}
	if (maxGap == 0) {
		addedBoards = M;
		return;
	}
	boards[addedBoards] = toCover[index];
	addedBoards++;
	for (int i = 0; i < maxGap - 1; i++) {
		stalls[toCover[index] + i] = false;
	}
}

int main() {
	FILE* fin = fopen("barn1.in", "r"), * fout = fopen("barn1.out", "w");
	int S;
	fscanf(fin, "%d %d %d", &M, &S, &C);
	bool* stalls = new bool[S];
	memset(stalls, false, S);
	int* toCover = new int[C];
	memset(toCover, 0, C * sizeof(int));
	int* boards = new int[M];
	memset(boards, 0, M * sizeof(int));
	for (int i = 0; i < C; i++) {
		fscanf(fin, "%d", &toCover[i]);
	}
	fclose(fin);
	sort(toCover, C);
	for (int i = toCover[0] - 1; i <= toCover[C - 1] - 1; i++) {
		stalls[i] = true;
	}
	for (int i = 1; i <= M; i++) {
		if (addedBoards == M - 1) {
			// subtract one because we have already place a large "board"
			break;
		}
		addBoard(toCover, stalls, boards);
	}
	int coveredStalls = 0;
	for (int i = 0; i < S; i++) {
		if (stalls[i] == true) {
			coveredStalls++;
		}
	}
	fprintf(fout, "%d\n", coveredStalls);
	fclose(fout);
}