/*
ID: ruifanl1
TASK: palsquare
LANG: C++
*/

#include <fstream>
#include <string.h>

int B = 0;

char returnChar(int num) {
	if (num == 1) {
		return '1';
	}
	if (num == 2) {
		return '2';
	}
	if (num == 3) {
		return '3';
	}
	if (num == 4) {
		return '4';
	}
	if (num == 5) {
		return '5';
	}
	if (num == 6) {
		return '6';
	}
	if (num == 7) {
		return '7';
	}
	if (num == 8) {
		return '8';
	}
	if (num == 9) {
		return '9';
	}
	if (num == 10) {
		return 'A';
	}
	if (num == 11) {
		return 'B';
	}
	if (num == 12) {
		return 'C';
	}
	if (num == 13) {
		return 'D';
	}
	if (num == 14) {
		return 'E';
	}
	if (num == 15) {
		return 'F';
	}
	if (num == 16) {
		return 'G';
	}
	if (num == 17) {
		return 'H';
	}
	if (num == 18) {
		return 'I';
	}
	if (num == 19) {
		return 'J';
	}
	return '0';
}

bool isPalindrome(char* num) {
	int len = strlen(num);
	int start = 0;
	int end = len - 1;
	while (start < end) {
		if (num[start] != num[end]) {
			return false;
		}
		start++;
		end--;
	}
	return true;
}

void convertToBase(int n, char *output, int max) {
	int remainder = 0;
	memset(output, '\0', max);
	while (n != 0) {

		char* tmpNum = new char[max];
		memset(tmpNum, '\0', max);
		int tmp = 0;
		while (output[tmp] != '\0') {
			tmpNum[tmp + 1] = output[tmp];
			tmp++;
		}
		memcpy(output, tmpNum, max);
		delete[] tmpNum;

		remainder = n % B;
		char c = returnChar(remainder);
		output[0] = c;
		n -= remainder;
		n /= B;
	}
}

int main() {
	char output[18];
	char NbaseB[10];
	FILE* fin = fopen("palsquare.in", "r"), * fout = fopen("palsquare.out", "w");
	fscanf(fin, "%d", &B);
	fclose(fin);
	for (int i = 1; i <= 300; i++) {
		int square = i * i;
		convertToBase(square, output, 18);
		if (isPalindrome(output)) {
			convertToBase(i, NbaseB, 10);
			fprintf(fout, "%s %s\n", NbaseB, output);
		}
	}
	fclose(fout);
}