
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

int N = 0;

void sort(int* array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (array[i] > array[j])
            {
                int value = array[i];
                array[i] = array[j];
                array[j] = value;
            }
        }
    }
}



int main()
{
    FILE* fin, * fout;
    fin = fopen("milk2.in", "r");
    fscanf_s(fin, "%d", &N);

    int* schedule = new int[N * 2 + 1];
    int* markers = new int[N * 2 + 1];

    memset(schedule, 0, sizeof(int) * N * 2);
    memset(markers, 0, sizeof(int) * N * 2);

    for (int i = 1; i <= N; i++)
    {
        fscanf_s(fin, "%d %d", &schedule[i * 2 - 1], &schedule[i * 2]);
        fscanf_s(fin, "%d %d", &markers[i * 2 - 1], &markers[i * 2]);
    }

    fclose(fin);

    int nFlags = N * 2;
    for (int i = 0; i < N * 2; i++) {
        for (int j = i; j < N * 2; i++) {
            if (i != j && markers[i] == markers[j]) {
                markers[j] = 1000000;
                nFlags--;
            }
        }
    }

    bool* flags = new bool[nFlags + 1];
    memset(flags, 0, nFlags);

    sort(markers, N * 2 + 1);
    for (int i = 1; i <= N; i++) {
        int start = 0;
        int end = 0;
        while (schedule[i * 2 - 1] != markers[start]) {
            start++;
        }
        end = start;
        while (schedule[i * 2] != markers[end]) {
            end++;
        }
        for (int j = 1; j <= end - start; j++) {
            flags[start + j] = 1;
        }
    }

    int pos = 0;
    int workingTime = 0;
    int noWorkTime = 0;

    while (pos <= nFlags) {
        int time = 0;
        int startPos = pos;
        while (pos <= nFlags && flags[pos] == 1) {
            pos++;
        }
        time = markers[pos - 1] - markers[startPos];
        if (startPos == 0) {
            time += markers[startPos];
        }
        if (time > workingTime) {
            workingTime = time;
        }
        startPos = pos;
        while (pos <= nFlags && flags[pos] == 0) {
            pos++;
        }
        time = markers[pos - 1] - markers[startPos];
    }

    fout = fopen("milk2.out", "w");
    fscanf_s(fout, "%d %d\n", &workingTime, &noWorkTime);

    fclose(fout);

    delete[] schedule;
    delete[] markers;
    delete[] flags;
}
