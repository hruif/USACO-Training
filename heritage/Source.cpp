/*
ID: ruifanl1
TASK: heritage
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<char> in, pre, ans;

void eraseNode(vector<char>& a, int node) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == node) {
			a.erase(a.begin() + i);
			return;
		}
	}
}

void searchPost(vector<char> usedIn, vector<char> usedPre) {
	int len = usedIn.size();
	if (len == 1) {
		ans.push_back(usedIn[0]);
		return;
	}
	char root = usedPre[0];
	int p;
	for (int i = 0; i < len; i++) {
		if (usedIn[i] == root) {
			p = i;
			break;
		}
	}
	vector<char> nextIn, nextPre;
	if (p == 0) {
		for (int i = 1; i < len; i++) {
			nextIn.push_back(usedIn[i]);
			nextPre.push_back(usedPre[i]);
		}
		searchPost(nextIn, nextPre);
	}
	else {
		nextPre = usedPre;
		for (int i = 0; i < p; i++) {
			nextIn.push_back(usedIn[i]);
		}
		for (int i = p; i < len; i++) {
			eraseNode(nextPre, usedIn[i]);
		}
		searchPost(nextIn, nextPre);
		nextIn.clear();
		nextPre = usedPre;
		for (int i = p + 1; i < len; i++) {
			nextIn.push_back(usedIn[i]);
		}
		if (nextIn.size() > 0) {
			for (int i = 0; i <= p; i++) {
				eraseNode(nextPre, usedIn[i]);
			}
			searchPost(nextIn, nextPre);
		}
	}
	ans.push_back(root);
}

int main() {
	ifstream fin("heritage.in");
	char buff;
	int len = 0;
	while (fin.get(buff)) {
		if (buff == '\n') {
			break;
		}
		in.push_back(buff);
		len++;
	}
	while (fin.get(buff)) {
		if (buff == '\n') {
			break;
		}
		pre.push_back(buff);
	}

	searchPost(in, pre);

	ofstream fout("heritage.out");
	for (int i = 0; i < len; i++) {
		fout << ans[i];
	}
	fout << '\n';
}