/*
ID: ruifanl1
TASK: friday
LANG: C++
*/

#include <fstream>
#include <iostream>

int nameDays[7];
int currentNameDay = 2;

using namespace std;

void checkFor13th(int month, int months[]) {
	for (int i = 1; i <= months[month]; i++) {
		if (i == 13) {
			nameDays[currentNameDay]++;
		}
		currentNameDay++;
		if (currentNameDay > 6) {
			currentNameDay = 0;
		}
	}
}

void count13ths(int year, int months[]) {
	if (year % 100 == 0) {
		if (year % 400 == 0) {
			months[1] = 29;
		}
	}
	else if (year % 4 == 0){
		months[1] = 29;
	}
	else {
		months[1] = 28;
	}
	for (int i = 0; i < 12; i++) {
		checkFor13th(i, months);
	}
}

int main() {
	ifstream fid("friday.in");
	ofstream fout("friday.out");
	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int year = 1900;
	unsigned int N;
	fid >> N;
	fid.close();
	for (int i = year; i < year + N; i++) {
		count13ths(i, months);
	}
	for (int i = 0; i < 6; i++) {
		fout << nameDays[i] << ' ';
	}
	fout << nameDays[6] << '\n';
	fout.close();
}