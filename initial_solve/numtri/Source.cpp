/*
ID: ruifanl1
TASK: numtri
LANG: C++
*/

#include <fstream>
#include <string.h>

using namespace std;

int R, numbers[1000][1000], sum[1000][1000];

long long calls = 0;

int search(int row, int index)
{
	calls++;
	if (sum[row][index] >= 0) {
		return sum[row][index];
	}
	int nodeSum = numbers[row][index];
	if (row == R - 1) {
		return nodeSum;
	}
	int leftsum = search(row + 1, index);
	int rightsum = search(row + 1, index + 1);
	sum[row][index] = leftsum > rightsum ? leftsum : rightsum;
	sum[row][index] += nodeSum;
	return sum[row][index];
}

int main()
{
	FILE* fin = fopen("numtri.in", "r"), * fout = fopen("numtri.out", "w");
	char newLine;
	fscanf(fin, "%d\n", &R);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < i + 1; j++) {
			fscanf(fin, "%d", &numbers[i][j]);
		}
	}
	fclose(fin);

	memset(sum, -1, sizeof(sum));
	int ans = search(0, 0);

	fprintf(fout, "%d\n", ans);
	fclose(fout);
}