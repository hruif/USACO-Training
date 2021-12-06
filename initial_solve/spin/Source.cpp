/*
ID: ruifanl1
TASK: spin
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> speeds;
vector<vector<vector<int>>> wheels;

bool isAlign(vector<vector<int>>& Wh1, vector<bool>& aligned, int wheel, int s) {
	vector<bool> wedges(360, false);
	for (int i = 0; i < Wh1.size(); i++) {
		int moved = s * speeds[wheel];
		int left = Wh1[i][0] + moved;
		int right = left + Wh1[i][1];
		if (right < left) {
			right += 360;
		}
		for (int d = left; d <= right; d++) {
			wedges[d % 360] = true;
		}
	}
	for (int i = 0; i < 360; i++) {
		if (!(aligned[i] && wedges[i])) {
			aligned[i] = false;
		}
	}
	for (int i = 0; i < 360; i++) {
		if (aligned[i]) {
			return true;
		}
	}
	return false;
}

bool canAlign(int s) {
	vector<bool> aligned(360, false);
	for (int i = 0; i < 5; i++) {
		if (i == 0) {
			for (int j = 0; j < wheels[i].size(); j++) {
				int moved = s * speeds[i];
				int left = wheels[i][j][0] + moved;
				int right = left + wheels[i][j][1];
				if (right < left) {
					right += 360;
				}
				for (int d = left; d <= right; d++) {
					aligned[d % 360] = true;
				}
			}
		}
		else {
			if (!isAlign(wheels[i], aligned, i, s)) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	ifstream fin("spin.in");
	for (int i = 0; i < 5; i++) {
		vector<vector<int>> wheel;
		int speed, W;
		fin >> speed >> W;
		speeds.push_back(speed);
		for (int i = 0; i < W; i++) {
			int a, b;
			vector<int> wedge;
			fin >> a >> b;
			wedge.push_back(a);
			wedge.push_back(b);
			wheel.push_back(wedge);
		}
		wheels.push_back(wheel);
	}

	int ans = -1;
	for (int i = 0; i < 360; i++) {
		if (canAlign(i)) {
			ans = i;
			break;
		}
	}

	ofstream fout("spin.out");
	if (ans == -1) {
		fout << "none";
	}
	else {
		fout << ans;
	}
	fout << '\n';
}