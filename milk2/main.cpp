/*
ID: ruifanl1
TASK: milk2
LANG: C++
*/

#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

int N = 0;

void sort(int *array, int n)
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
    FILE *fin, *fout;
    fin = fopen("milk2.in", "r");
    fscanf(fin, "%d", &N);

    int *schedule= new int[N * 2];
    int *markers = new int [N * 2];

    memset(schedule, 0, sizeof(int) * N * 2);
    memset(markers, 0, sizeof(int) * N * 2);

    for (int i = 0; i < N; i++)
    {
        fscanf(fin, "%d %d", &schedule[i * 2], &schedule[i * 2 + 1]);
    }
    memcpy(markers, schedule, sizeof(int) * N * 2);

    fclose(fin);

    int nFlags = N * 2;
    int endPos = nFlags - 1;
    for (int i = 0; i <= endPos - 1; i++) {
        for (int j = i + 1; j <= endPos; j++) {
            if (markers[i] == markers[j]) {
                while (true) {
                    if (markers[endPos] != markers[j] || endPos <= j) {
                        int tmp = markers[endPos];
                        markers [endPos] = markers[j];
                        markers [j] = tmp;
                        endPos--;
                        break;
                    }
                    endPos--;
                }
            }
        }
    }
    nFlags = endPos + 1;
    bool *flags = new bool[nFlags];
    memset(flags, 0, nFlags);

    sort(markers, nFlags);
    for (int i = 0; i < N; i++) {
        int start = 0;
        int end = 0;
        while (schedule[i * 2] != markers[start]) {
            start++;
        }
        end = start;
        while (schedule[i * 2 + 1] != markers[end]) {
            end++;
        }
        for (int j = start; j < end; j++) {
            flags[j + 1] = true;
        }
    }

    int pos = 1;
    int workingTime = 0;
    int noWorkingTime = 0;

    while (pos < nFlags) {
        int time = 0;
        int startPos = pos - 1;
        while (pos < nFlags && flags[pos] == true) {
            pos++;
        }
        time = markers[pos - 1] - markers[startPos];
        if (time > workingTime) {
            workingTime = time;
        }
        startPos = pos - 1;
        while (pos < nFlags && flags[pos] == false) {
            pos++;
        }
        time = markers[pos - 1] - markers[startPos];
        if (time > noWorkingTime) {
            noWorkingTime = time;
        }
    }

    fout = fopen("milk2.out", "w");
    fprintf(fout, "%d %d\n", workingTime, noWorkingTime);

    fclose(fout);

    delete[] schedule;
    delete[] markers;
    delete[] flags;
}
