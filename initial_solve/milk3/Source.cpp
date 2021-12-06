/*
ID: ruifanl1
TASK: milk3
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int milk[3], capacity[3], answers[21], numOfAns, combos[8000][3], numOfCombos;

void pour(int from, int to)
{
	if (milk[from] == 0 || milk[to] == capacity[to]) {
		return;
	}

	int transfer = capacity[to] - milk[to];
	if (transfer > milk[from]) {
		transfer = milk[from];
	}
	milk[from] -= transfer;
	milk[to] += transfer;

	for (int i = 0; i < numOfCombos; i++) {
		if (milk[0] == combos[i][0] && milk[1] == combos[i][1] && milk[2] == combos[i][2]) {
			milk[from] += transfer;
			milk[to] -= transfer;
			return;
		}
	}
	combos[numOfCombos][0] = milk[0];
	combos[numOfCombos][1] = milk[1];
	combos[numOfCombos][2] = milk[2];
	numOfCombos++;

	if (milk[0] == 0) {
		answers[numOfAns] = milk[2];
		numOfAns++;
	}
	pour(0, 1);
	pour(0, 2);
	pour(1, 0);
	pour(1, 2);
	pour(2, 0);
	pour(2, 1);
	milk[from] += transfer;
	milk[to] -= transfer;
}

int main()
{
	char a = -1;
	unsigned char b = 0b11111111;
	unsigned int d = (int)b;
	unsigned int e = 0b11111111111111111111111111111111;
	unsigned int e2 = 0b00000000000000000000000011111111;

	bool c = a == b;
	bool f = d == e2;


	return 0;
	ifstream fin("milk3.in");
	ofstream fout("milk3.out");
	fin >> capacity[1] >> capacity[1] >> capacity[2];

	milk[2] = capacity[2];
	answers[0] = milk[2];
	numOfAns++;
	combos[numOfCombos][0] = milk[0];
	combos[numOfCombos][1] = milk[1];
	combos[numOfCombos][2] = milk[2];
	numOfCombos++;
	pour(2, 0);
	pour(2, 1);
	
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