/*
ID: ruifanl1
TASK: gift1
LANG: C++
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

class Friend {
public:
    char name[20];
    int initialAmount;
    int numberOfGiftsGiven;
    char friends[10][20];
    int balance = 0;
};

int findFriendByName(char name[], Friend friends[], int NP) {
    for (int i = 0; i < NP; i++) {
        if (strcmp(name, friends[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void giveGifts(Friend friends[], int friendIndex, int NP) {
    Friend &giver = friends[friendIndex];
    if (giver.numberOfGiftsGiven != 0) {
        int moneyToKeep = giver.initialAmount % giver.numberOfGiftsGiven;
        giver.balance += moneyToKeep;
        int moneyToGive = (giver.initialAmount - moneyToKeep) / giver.numberOfGiftsGiven;
        for (int i = 0; i < giver.numberOfGiftsGiven; i++) {
            int receiverIndex = findFriendByName(giver.friends[i], friends, NP);
            Friend& receiver = friends[receiverIndex];
            receiver.balance += moneyToGive;
        }
    }
    else {
        giver.balance += giver.initialAmount;
    }
    giver.balance -= giver.initialAmount;
}

int readInputFile(Friend friends[]) {
    ifstream fid("gift1.in");
    int NP;
    fid >> NP;
    for (int i = 0; i < NP; i++) {
        fid >> friends[i].name;
    }
    for (int i = 0; i < NP; i++) {
        char name[20];
        fid >> name;
        int friendIndex = findFriendByName(name, friends, NP);
        fid >> friends[friendIndex].initialAmount >> friends[friendIndex].numberOfGiftsGiven;
        for (int j = 0; j < friends[friendIndex].numberOfGiftsGiven; j++) {
            fid >> friends[friendIndex].friends[j];
        }
    }
    fid.close();
    return NP;
}

int main() {
    ofstream fout("gift1.out");
    Friend friends[10];
    int NP = readInputFile(friends);
    for (int i = 0; i < NP; i++) {
        giveGifts(friends, i, NP);
    }
    for (int i = 0; i < NP; i++) {
        fout << friends[i].name << ' ' << friends[i].balance << '\n';
    }
    fout.close();
}