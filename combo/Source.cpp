/*
ID: ruifanl1
TASK: combo
LANG: C++
*/

#include <fstream>

int N;

int moveDigit(int current, int offset) {
	current += offset;
	while (current < 1) {
		current += N;
	}
	while (current > N) {
		current -= N;
	}
	return current;
}

bool checkNoCopies(int* list, int item, int len) {
	for (int i = 0; i < len; i++) {
		if (list[i] == item) {
			return false;
		}
	}
	return true;
}

int findDigits(int* array, int* farmer, int* master, int digit) {
	digit--;
	array[0] = moveDigit(farmer[digit], -2);
	int arrayLen = 1;
	for (int i = -1; i < 3; i++) {
		if (checkNoCopies(array, moveDigit(farmer[digit], i), arrayLen)) {
			array[arrayLen] = moveDigit(farmer[digit], i);
			arrayLen++;
		}
	}
	for (int i = -2; i < 3; i++) {
		if (checkNoCopies(array, moveDigit(master[digit], i), arrayLen)) {
			array[arrayLen] = moveDigit(master[digit], i);
			arrayLen++;
		}
	}
	return arrayLen;
}

int main() {
	FILE* fin = fopen("combo.in", "r"), * fout = fopen("combo.out", "w");
	int farmer[3], master[3], digitOne[10], digitTwo[10], digitThree[10];
	fscanf(fin, "%d%d%d%d%d%d%d", &N, &farmer[0], &farmer[1], &farmer[2], &master[0], &master[1], &master[2]);
	fclose(fin);

	int firstLen = findDigits(digitOne, farmer, master, 1);
	int secondLen = findDigits(digitTwo, farmer, master, 2);
	int thirdLen = findDigits(digitThree, farmer, master, 3);

	firstLen = 10 - firstLen;
	secondLen = 10 - secondLen;
	thirdLen = 10 - thirdLen;

	int overlapAnswers = firstLen * secondLen * thirdLen;
	int minAnswer = 0;
	int totalAnswers;
	if (N < 5) {
		totalAnswers = N * N * N;
	}
	else {
		totalAnswers = 250 - overlapAnswers;
	}

	fprintf(fout, "%d\n", totalAnswers);
	fclose(fout);
}