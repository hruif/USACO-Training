/*
ID: ruifanl1
TASK: milk3
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int A[2], B[2], C[2], answers[21], numOfAns, combos[8000][3], numOfCombos;

void pour(int* from, int* to)
{
	int storeFrom = from[1], storeTo = to[1];
	if (from[1] == 0 || to[1] == to[0]) {
		return;
	}

	if (to[1] + from[1] > to[0]) {
		int tmp = to[0] - to[1];
		to[1] = to[0];
		from[1] -= tmp;
	}
	else {
		to[1] += from[1];
		from[1] = 0;
	}

	for (int i = 0; i < numOfCombos; i++) {
		if (A[1] == combos[i][0] && B[1] == combos[i][1]) {
			from[1] = storeFrom;
			to[1] = storeTo;
			return;
		}
	}
	combos[numOfCombos][0] = A[1];
	combos[numOfCombos][1] = B[1];
	combos[numOfCombos][2] = C[1];
	numOfCombos++;

	if (A[1] == 0) {
		answers[numOfAns] = C[1];
		numOfAns++;
	}
	pour(A, B);
	pour(A, C);
	pour(B, A);
	pour(B, C);
	pour(C, A);
	pour(C, B);
	from[1] = storeFrom;
	to[1] = storeTo;
}

int main()
{
	ifstream fin("milk3.in");
	ofstream fout("milk3.out");
	fin >> A[0] >> B[0] >> C[0];

	C[1] = C[0];
	answers[0] = C[1];
	numOfAns++;
	combos[numOfCombos][0] = A[1];
	combos[numOfCombos][1] = B[1];
	combos[numOfCombos][2] = C[1];
	numOfCombos++;
	pour(C, B);
	pour(C, A);
	
	sort(answers, answers + numOfAns);
	for (int i = 0; i < numOfAns; i++) {
		if (i > 0) {
			fout << ' ';
		}
		fout << answers[i];
	}
	fout << '\n';
	fout.close();
}