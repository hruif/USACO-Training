/*
ID: ruifanl1
PROG: ride
LANG: C++
*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int computeNameValue(string name) {
	int value = 1;
	for (unsigned i = 0; i < name.length(); ++i) {
		char c = name.at(i);
		if (isupper(c)) {
			c = c - 'A' + 1;
		}
		else {
			c = c - 'a' + 1;
		}
		value *= c;
	}
	return value;
}

bool checkGo(string cometName, string groupName) {
	int cometValue = computeNameValue(cometName);
	int groupValue = computeNameValue(groupName);

	return groupValue % 47 == cometValue % 47;
}

int main2() {
	ofstream fout("ride.out");
	ifstream fid("ride.in");
	string groupName;
	string cometName;
	fid >> groupName;
	fid >> cometName;
	if (checkGo(cometName, groupName) == true) {
		fout << "GO\n";
	}
	else {
		fout << "STAY\n";
	}
	return 0;
}