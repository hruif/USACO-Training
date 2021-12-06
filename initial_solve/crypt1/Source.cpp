/*
ID: ruifanl1
TASK: crypt1
LANG: C++
*/

#include <fstream>
#include <string.h>

int N;

int findProduct(int digit, char* twoDigit, char* threeDigit, char* productArray) {
	int tmpOnes = (int)twoDigit[digit] * (int)threeDigit[0];
	int tmpTens = tmpOnes;
	tmpOnes %= 10;
	tmpTens -= tmpOnes;
	tmpTens /= 10;
	productArray[0] = tmpOnes;

	tmpOnes = (int)twoDigit[digit] * (int)threeDigit[1];
	tmpOnes += tmpTens;
	tmpTens = tmpOnes;
	tmpOnes %= 10;
	tmpTens -= tmpOnes;
	tmpTens /= 10;
	productArray[1] = tmpOnes;

	tmpOnes = (int)twoDigit[digit] * (int)threeDigit[2];
	tmpOnes += tmpTens;
	tmpTens = tmpOnes;
	tmpOnes %= 10;
	tmpTens -= tmpOnes;
	productArray[2] = tmpOnes;

	return tmpTens;
}

bool checkFalse(char* productArray, int* digits, int len) {
	for (int i = 0; i < len; i++) {
		int tmp = 0;
		for (int j = 0; j < N; j++) {
			if (productArray[i] != digits[j]) {
				tmp++;
			}
			else {
				break;
			}
			if (tmp == N) {
				return true;
			}
		}
	}
	return false;
}

bool checkWork(char* threeDigit, char* twoDigit, char* productOne, char* productTwo, char* productFinal, int* digits) {
	int firstDigit = findProduct(0, twoDigit, threeDigit, productOne);
	if (firstDigit > 0 || productOne[2] == 0) {
		return false;
	}
	firstDigit = findProduct(1, twoDigit, threeDigit, productTwo);
	if (firstDigit > 0 || productTwo[2] == 0) {
		return false;
	}

	productFinal[0] = productOne[0];
	for (int i = 0; i < 2; i++) {
		int tmpOnes = productOne[i + 1] + productTwo[i] + firstDigit;
		firstDigit = tmpOnes;
		tmpOnes %= 10;
		firstDigit -= tmpOnes;
		productFinal[i + 1] = tmpOnes;
		firstDigit /= 10;
	}
	productFinal[3] = productTwo[2] + firstDigit;
	if (productFinal[3] >= 10) {
		return false;
	}

	if (checkFalse(productOne, digits, 3)) {
		return false;
	}
	if (checkFalse(productTwo, digits, 3)) {
		return false;
	}
	if (checkFalse(productFinal, digits, 4)) {
		return false;
	}
	return true;
}

int main() {
	FILE* fin = fopen("crypt1.in", "r"), * fout = fopen("crypt1.out", "w");
	char threeDigit[3], twoDigit[2], productOne[3], productTwo[3], productFinal[4];
	int digits[10];
	int totalAnswers = 0;
	fscanf(fin, "%d", &N);
	for (int i = 0; i < N; i++) {
		fscanf(fin, "%d", &digits[i]);
	}
	fclose(fin);
	for (int i = 0; i < N; i++) {
		threeDigit[0] = digits[i];
		for (int j = 0; j < N; j++) {
			threeDigit[1] = digits[j];
			for (int k = 0; k < N; k++) {
				threeDigit[2] = digits[k];
				for (int l = 0; l < N; l++) {
					twoDigit[0] = digits[l];
					for (int x = 0; x < N; x++) {
						twoDigit[1] = digits[x];
						if (checkWork(threeDigit, twoDigit, productOne, productTwo, productFinal, digits)) {
							totalAnswers++;
						}
					}
				}
			}
		}
	}
	fprintf(fout, "%d\n", totalAnswers);

	fclose(fout);
}