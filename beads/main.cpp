/*
ID: ruifanl1
TASK: beads
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int n;

int moveBreakpoint(int initialPos, int direction) {
    if (initialPos + direction < 0) {
        return n + (initialPos + direction);
    }
    if (initialPos + direction >= n) {
        return initialPos + direction - n;
    }
    return initialPos + direction;
}

char getColor(int breakpoint, char *necklace, int direction) {
    if (direction == 1) {
        return necklace[breakpoint];
    }
    if (direction == -1) {
        return necklace[moveBreakpoint(breakpoint, -1)];
    }
    return ' ';
}

char findColor(int breakpoint, char *necklace, int direction) {
    for (int i = 0; i < n; i++) {
        char color = getColor(breakpoint, necklace, direction);
        if (color != 'w') {
            return color;
        }
        breakpoint = moveBreakpoint(breakpoint, direction);
    }
    return 'w';
}

int countFromPoint(int breakpoint, char *necklace) {
    char leftColor = findColor(breakpoint, necklace, -1);
    if (leftColor == 'w') {
        return n;
    }
    char rightColor = findColor(breakpoint, necklace, 1);
    int beadsInGroup = 0;
    int position = breakpoint;
    char beanColor;
    do {
        beanColor = getColor(position, necklace, -1);
        position = moveBreakpoint(position, -1);
        beadsInGroup++;
        if (beadsInGroup == n) {
            return n;
        }
    } while (beanColor == leftColor || beanColor == 'w');
    position = breakpoint;
    do {
        beanColor = getColor(position, necklace, 1);
        position = moveBreakpoint(position, 1);
        beadsInGroup++;
    } while (beanColor == rightColor || beanColor == 'w');
    beadsInGroup -= 2;
    if (beadsInGroup > n) {
        return n;
    }
    return beadsInGroup;
}

int main()
{
    FILE *fin, *fout;
    fin = fopen("beads.in", "r");
    fscanf(fin, "%d", &n);
    char *necklace = new char [n + 1];
    fscanf(fin, "%s", necklace);
    fclose(fin);
    int largest = 0;
    for (int i = 0; i < n; i++) {
        int beads = countFromPoint(i, necklace);
        if (beads > largest) {
            largest = beads;
        }
    }
    fout = fopen("beads.out", "w");
    fprintf(fout, "%d\n", largest);
    fclose(fout);
    delete[] necklace;
}
