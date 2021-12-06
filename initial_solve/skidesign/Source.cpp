/*
ID: ruifanl1
TASK: skidesign
LANG: C++
*/

#include <fstream>
#define MAX_HEIGHT 100

int N, hills[1000];

int adjustHills(int minHeight)
{
	int totalCost = 0;
	for (int i = 0; i < N; i++) {
		int heightDiff = hills[i] - minHeight;
		int changed = 0;
		while (heightDiff > 17) {
			heightDiff--;
			changed++;
		}
		while (heightDiff < 0) {
			heightDiff++;
			changed++;
		}
		int cost = changed * changed;
		totalCost += cost;
	}
	return totalCost;
}

int main()
{
	int ans = -1;
	FILE* fin = fopen("skidesign.in", "r"), * fout = fopen("skidesign.out", "w");
	fscanf(fin, "%d", &N);
	for (int i = 0; i < N; i++) {
		fscanf(fin, "%d\n", &hills[i]);
	}
	fclose(fin);

	for (int i = 0; i <= MAX_HEIGHT; i++) {
		int tmp = adjustHills(i);
		if (tmp < ans || ans < 0) {
			ans = tmp;
		}
	}
	fprintf(fout, "%d\n", ans);
	fclose(fout);
}