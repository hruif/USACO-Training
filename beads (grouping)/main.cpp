/*
ID: ruifanl1
TASK: beads
LANG: C++
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

// A "group" is a part of the necklace (multiple adjacent beads) containing only one color.
// A "grouped" necklace is the given necklace but each spot represents the number and color of beads in a single group.

int n;

int next(int initialPos, int direction, int len) {
    if (direction != 1 && direction != -1) {
        exit(-1);
    }
    if (initialPos + direction < 0) {
        return len + (initialPos + direction);
    }
    if (initialPos + direction >= len) {
        return initialPos + direction - len;
    }
    return initialPos + direction;
}

int findGroups(char *necklace, char *groupColors, int *groupSizes) {
    int pos = 0, groups = 0, counter = 0;
    char color = necklace[0];
    while (necklace[pos] == color) {
        pos = next(pos, 1, n);
        counter++;
        if (counter == n) {
            groupSizes[0] = n;
            return 1;
        }
    }
    // Skips over first group because could be incomplete. If first group goes through entire array returns.
    color = necklace[pos];
    while (counter <= n) {
        while (necklace[pos] == color) {
            counter++;
            groupSizes[groups]++;
            pos = next(pos, 1, n);
        }
        groupColors[groups] = color;
        color = necklace[pos];
        groups++;
    }
    // Goes through "groups" of beads with the number and color in the same indexes of different arrays.
    return groups;
}

int combineGroups (char *colors, int *sizes, int groups, char *new_colors, int *new_sizes) {
// int function returns number of groups after combining.
    int new_len = -1;
    // int variable used to represent place in final necklace.
    int pos = 0;
    // int variable to represent starting bead.
    while (colors[pos] == 'w') {
        pos++;
    }
    char color1 = colors[pos];
    while (colors[pos] == 'w' || colors[pos] == color1) {
        pos++;
        if (pos >= n) {
            new_sizes[0] = n;
            new_colors[0] = color1;
            return 1;
        }
    }
    // while loop makes sure starting bead is not white.
    for (int i = 0; i < groups; i++) {
    // Checks all beads but the last one.
        if (colors[pos] == 'w' && new_colors[new_len] == colors[next(pos, 1, groups)]) {
        // When the two colors on either side of a white group are the same:
            new_sizes[new_len] += sizes[next(pos, 1, groups)] + sizes[pos];
            pos = next(pos, 1, groups);
            i++;
        }
        else {
            new_len++;
            new_colors[new_len] = colors[pos];
            new_sizes[new_len] = sizes[pos];
        }
        pos = next(pos, 1, groups);
    }
    return new_len + 1;
    // Returns the amount of groups.
}

int checkLargestGroup (char *new_colors, int *new_sizes, int groups) {
    int largest = 0;
    // Variable to hold answer to problem.
    for (int i = 0; i < groups; i++) {
        int sumOfR = 0, sumOfL = 0;

        int r0 = i;
        int r1 = next(i, 1, groups);
        int r2 = next(r1, 1, groups);
        if (new_colors[r0] == 'w' || new_colors[r1] == 'w') {
            sumOfR = new_sizes[r0] + new_sizes[r1];
            if (new_colors[r2] == 'w' && r2 != r0) {
                sumOfR += new_sizes[r2];
            }
        }
        // If there is a white within two spaces in the positive direction, add the white and other color together to find total.
        else {
            sumOfR = new_sizes[i];
        }
        // If there is no white within two spaces in the positive direction, use the nearest color's number.
        int l0 = next(i, -1, groups);
        int l1 = next(l0, -1, groups);
        int l2 = next(l1, -1, groups);
        if (new_colors[l0] == 'w' || new_colors[l1] == 'w') {
            sumOfL = new_sizes[l0] + new_sizes[l1];
            if (new_colors[l2] == 'w' && l2 != l0) {
                sumOfL += new_sizes[l2];
            }
        }
        // If there is a white within two spaces in the negative direction, add the white and other color together to find total.
        else {
            sumOfL = new_sizes[l0];
        // If there is no white within two spaces in the negative direction, use the nearest color's number.
        }
        largest = std::max(sumOfR + sumOfL, largest);
        // Check to see if the pair of sums is greater than the current logged largest number.
    }
    return largest;
    // Return answer.
}

int main()
{
    FILE *fin, *fout;
    fin = fopen("beads.in", "r");
    fscanf(fin, "%d", &n);

    char *necklace = new char [n + 1];
    int *necklace2_sizes = new int [n + 1];
    char *necklace2_colors = new char [n + 1];
    int *necklace3_sizes = new int [n + 1];
    char *necklace3_colors = new char [n + 1];

    memset(necklace, 0, n + 1);
    memset(necklace2_sizes, 0, (n + 1) * sizeof(int));
    memset(necklace2_colors, 0, n + 1);
    memset(necklace3_sizes, 0, (n + 1) * sizeof(int));
    memset(necklace3_colors, 0, n + 1);

    fscanf(fin, "%s", necklace);
    fclose(fin);

    int necklace2_groups = findGroups(necklace, necklace2_colors, necklace2_sizes);
    int largest = n;
    if (necklace2_groups > 3) {
        int necklace3_groups = combineGroups(necklace2_colors, necklace2_sizes, necklace2_groups, necklace3_colors, necklace3_sizes);
        largest = checkLargestGroup(necklace3_colors, necklace3_sizes, necklace3_groups);
    }
    fout = fopen("beads.out", "w");
    fprintf(fout, "%d\n", largest);
    fclose(fout);
    delete[] necklace;
    delete[] necklace2_sizes;
    delete[] necklace2_colors;
    delete[] necklace3_sizes;
    delete[] necklace3_colors;
}
