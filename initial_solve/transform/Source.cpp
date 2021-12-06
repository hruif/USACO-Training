/*
ID: ruifanl1
TASK: transform
LANG: C++
*/

#include <fstream>
#include <string.h>

int N = 0;
char** finalPattern;

void copyPattern(char** destination, char** source) {
	for (int i = 0; i < N; i++) {
		memcpy(destination[i], source[i], N);
	}
}

char** newPattern() {
	char** tmpPattern = new char* [N];
	for (int i = 0; i < N; i++) {
		tmpPattern[i] = new char[N];
		memset(tmpPattern[i], 0, N);
	}
	return tmpPattern;
}

void releasePattern(char** tmpPattern) {
	for (int i = 0; i < N; i++) {
		delete[] tmpPattern[i];
	}
	delete[] tmpPattern;
}

void rotate90(char** pattern) {
	char **tmpPattern = newPattern();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmpPattern[i][j] = pattern[N - 1 - j][i];
		}
	}
	copyPattern(pattern, tmpPattern);
	releasePattern(tmpPattern);
}

bool checkSame(char** initialPattern) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (initialPattern[i][j] != finalPattern[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void reflect(char** pattern) {
	char** tmpPattern = newPattern();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmpPattern[i][j] = pattern[i][N - 1 - j];
		}
	}
	copyPattern(pattern, tmpPattern);
	releasePattern(tmpPattern);
}

int solve(char** initialPattern) {
	char** tmpPattern = newPattern();
	copyPattern(tmpPattern, initialPattern);
	rotate90(tmpPattern);
	if (checkSame(tmpPattern)) {
		return 1;
	}
	rotate90(tmpPattern);
	if (checkSame(tmpPattern)) {
		return 2;
	}
	rotate90(tmpPattern);
	if (checkSame(tmpPattern)) {
		return 3;
	}
	copyPattern(tmpPattern, initialPattern);
	reflect(tmpPattern);
	if (checkSame(tmpPattern)) {
		return 4;
	}
	for (int i = 0; i < 3; i++) {
		rotate90(tmpPattern);
		if (checkSame(tmpPattern)) {
			return 5;
		}
	}
	if (checkSame(initialPattern)) {
		return 6;
	}
	return 7;
}

int main() {
	FILE *fin, *fout;
	fin = fopen("transform.in", "r");
	fscanf(fin, "%d", &N);
	char** initialPattern = new char*[N];
	for (int i = 0; i < N; i++) {
		initialPattern[i] = new char[N];
		memset(initialPattern[i], 0, N);
	}
	char c = 0;
	fscanf(fin, "%c", &c);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N + 1; j++) {
			fscanf(fin, "%c", &c);
			if (c != '\n') {
				initialPattern[i][j] = c;
			}
		}
	}
	finalPattern = new char*[N];
	for (int i = 0; i < N; i++) {
		finalPattern[i] = new char[N];
		memset(finalPattern[i], 0, N);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N + 1; j++) {
			fscanf(fin, "%c", &c);
			if (c != '\n') {
				finalPattern[i][j] = c;
			}
		}
	}
	fclose(fin);

	int optionNum = solve(initialPattern);
	
	fout = fopen("transform.out", "w");
	fprintf(fout, "%d\n", optionNum);
	fclose(fout);
}