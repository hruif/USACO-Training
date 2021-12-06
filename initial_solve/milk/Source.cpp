/*
ID: ruifanl1
TASK: milk
LANG: C++
*/

#include <fstream>
#include <string.h>

int totalMilk = 0, nOfFarmers = 0;

int returnLow(int** farmers) {
	int low = 5001;
	int index = 0;
	for (int i = 0; i < nOfFarmers; i++) {
		if (farmers[i][0] < low && farmers[i][1] > 0) {
			index = i;
			low = farmers[i][0];
		}
	}
	return index;
}

int main() {
	FILE* fin = fopen("milk.in", "r"), *fout = fopen("milk.out", "w");
	int milkNeeded = 0, totalCost = 0;
	fscanf(fin, "%d %d", &milkNeeded, &nOfFarmers);
	int** farmers = new int* [nOfFarmers];
	for (int i = 0; i < nOfFarmers; i++) {
		farmers[i] = new int[2];
		memset(farmers[i], '\0', 2 * sizeof(int));
		fscanf(fin, "%d %d", &farmers[i][0], &farmers[i][1]);
	}
	int farmerIndex = returnLow(farmers);
	while (totalMilk < milkNeeded) {
		if (farmers[farmerIndex][1] == 0) {
			farmerIndex = returnLow(farmers);
		}
		totalMilk++;
		farmers[farmerIndex][1]--;
		totalCost += farmers[farmerIndex][0];
	}
	fprintf(fout, "%d\n", totalCost);
}