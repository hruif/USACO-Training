/*
ID: ruifanl1
TASK: msquare
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
bool found[8][8][8][8][8][8][8];
vector<int> mSquare, ans;
queue<vector<int>> magicSquares;
queue<vector<char>> transformations;

void A(vector<int>& original, vector<int>& copy) {
	copy[0] = original[7];
	copy[1] = original[6];
	copy[2] = original[5];
	copy[3] = original[4];
	copy[4] = original[3];
	copy[5] = original[2];
	copy[6] = original[1];
	copy[7] = original[0];
}

void B(vector<int>& original, vector<int>& copy) {
	copy[0] = original[3];
	copy[1] = original[0];
	copy[2] = original[1];
	copy[3] = original[2];
	copy[4] = original[5];
	copy[5] = original[6];
	copy[6] = original[7];
	copy[7] = original[4];
}

void C(vector<int>& original, vector<int>& copy) {
	copy[0] = original[0];
	copy[1] = original[6];
	copy[2] = original[1];
	copy[3] = original[3];
	copy[4] = original[4];
	copy[5] = original[2];
	copy[6] = original[5];
	copy[7] = original[7];
}

bool isAns(vector<int>& mSq) {
	for (int i = 0; i < 8; i++) {
		if (mSq[i] != ans[i]) {
			return false;
		}
	}
	return true;
}

bool isTrue(vector<int>& mSq) {
	if (found[mSq[0] - 1][mSq[1] - 1][mSq[2] - 1][mSq[3] - 1][mSq[4] - 1][mSq[5] - 1][mSq[6] - 1]) {
		return true;
	}
	found[mSq[0] - 1][mSq[1] - 1][mSq[2] - 1][mSq[3] - 1][mSq[4] - 1][mSq[5] - 1][mSq[6] - 1] = true;
	return false;
}

void transform() {
	vector<int> mSq;
	vector<char> transformation;
	for (int i = 1; i <= 8; i++) {
		mSq.push_back(i);
	}
	magicSquares.push(mSq);
	transformations.push(transformation);

	while (true) {
		vector<int> original = magicSquares.front();

		if (isAns(original)) {
			return;
		}

		if (!isTrue(original)) {
			vector<int> tmpMSq(8);
			vector<char> tmpTrans = transformations.front();
			A(original, tmpMSq);
			tmpTrans.push_back('A');
			transformations.push(tmpTrans);
			magicSquares.push(tmpMSq);

			int transLast = tmpTrans.size() - 1;

			B(original, tmpMSq);
			tmpTrans[transLast] = 'B';
			transformations.push(tmpTrans);
			magicSquares.push(tmpMSq);

			C(original, tmpMSq);
			tmpTrans[transLast] = 'C';
			transformations.push(tmpTrans);
			magicSquares.push(tmpMSq);
		}
		magicSquares.pop();
		transformations.pop();
	}
}

int main() {
	ifstream fin("msquare.in");
	for (int i = 0; i < 8; i++) {
		int tmp;
		fin >> tmp;
		ans.push_back(tmp);
	}

	transform();

	ofstream fout("msquare.out");
	int len = transformations.front().size();
	fout << len << '\n';
	for (int i = 0; i < len; i++) {
		if (i % 60 == 0 && i != 0) {
			fout << '\n';
		}
		fout << transformations.front()[i];
	}
	fout << '\n';
}