/*
ID: ruifanl1
TASK: dualpal
LANG: C++
*/

#include <fstream>
#include <string.h>

int N = 0, S = 0;

char returnChar(int num) {
	if (num <= 9) {
		return '0' + num;
	}
	else {
		return 'A' + (num - 10);
	}
}

bool isPalindrome(char* num) {
	int start = 0;
	int end = strlen(num) - 1;
	while (start < end) {
		if (num[start] != num[end]) {
			return false;
		}
		start++;
		end--;
	}
	return true;
}

void convertToBase(int n, char* output, int B) {
	int remainder = 0;
	memset(output, '\0', 32);
	while (n != 0) {
		char* tmpNum = new char[32];
		memset(tmpNum, '\0', 32);
		int tmp = 0;
		while (output[tmp] != '\0') {
			tmpNum[tmp + 1] = output[tmp];
			tmp++;
		}
		memcpy(output, tmpNum, 32);
		delete[] tmpNum;
		remainder = n % B;
		char c = returnChar(remainder);
		output[0] = c;
		n -= remainder;
		n /= B;
	}
}

int main() {
	FILE* fin = fopen("dualpal.in", "r"), * fout = fopen("dualpal.out", "w");
	fscanf(fin, "%d %d", &N, &S);
	fclose(fin);
	char output[32];
	int totalVals = 0;
	while (true) {
		S++;
		int numBases = 0;
		for (int base = 2; base <= 10; base++) {
			convertToBase(S, output, base);
			if (isPalindrome(output)) {
				numBases++; 
				if (numBases > 1) {
					totalVals++;
					fprintf(fout, "%d\n", S);
					break;
				}
			}
		}
		if (totalVals >= N) {
			break;
		}
	}
	fclose(fout);
}