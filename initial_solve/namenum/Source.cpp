/*
ID: ruifanl1
TASK: namenum
LANG: C++
*/

#include <fstream>
#include <string.h>

void addName() {

}

char checkNum(char letter) {
	if (letter == 'A' || letter == 'B' || letter == 'C') {
		return '2';
	}
	if (letter == 'D' || letter == 'E' || letter == 'F') {
		return '3';
	}
	if (letter == 'G' || letter == 'H' || letter == 'I') {
		return '4';
	}
	if (letter == 'J' || letter == 'K' || letter == 'L') {
		return '5';
	}
	if (letter == 'M' || letter == 'N' || letter == 'O') {
		return '6';
	}
	if (letter == 'P' || letter == 'R' || letter == 'S') {
		return '7';
	}
	if (letter == 'T' || letter == 'U' || letter == 'V') {
		return '8';
	}
	if (letter == 'W' || letter == 'X' || letter == 'Y') {
		return '9';
	}
	return '0';
}

bool checkName(char* name, char* num) {
	int numLen = strlen(num);
	int nameLen = strlen(name);
	if (numLen != nameLen) {
		return false;
	}
	for (int i = 0; i < numLen; i++) {
		if (checkNum(name[i]) != num[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	FILE* fin, *fintext, *fout;
	char num[13];
	fin = fopen("namenum.in", "r");
	fscanf(fin, "%s", num);
	fintext = fopen("dict.txt", "r");
	char** dictNames = new char* [5000];
	for (int i = 0; i < 5000; i++) {
		dictNames[i] = new char[13];
	}
	int numNames = 0;
	for (int i = 0; i < 5000; i++) {
		if (fscanf(fintext, "%s", dictNames[i]) <= 0) {
			break;
		}
		numNames++;
	}
	fclose(fin);
	char** validNames = new char* [numNames];
	int numValidNames = 0;
	for (int i = 0; i < numNames; i++) {
		if (checkName(dictNames[i], num)) {
			validNames[numValidNames] = dictNames[i];
			numValidNames++;
		}
	}

	fout = fopen("namenum.out", "w");
	if (numValidNames == 0) {
		fprintf(fout, "NONE\n");
	}
	else {
		for (int i = 0; i < numValidNames; i++) {
			fprintf(fout, "%s\n", validNames[i]);
		}
	}
	fclose(fout);
	for (int i = 0; i < 5000; i++) {
		delete[] dictNames[i];
	}

	delete[] validNames;
	delete[] dictNames;
}