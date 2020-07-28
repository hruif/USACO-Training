/*
ID: ruifanl1
TASK: shuttle
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

struct state {
	int empty;
	string strip;
	vector<int> moves;
	int last;
	bool start;
};

bool found = false, in2 = false;
int N;
state ans;
unordered_set<string> foundStrips1, foundStrips2;

bool isDupe(state& c) {
	if (c.start) {
		if (foundStrips1.find(c.strip) != foundStrips1.end()) {
			return true;
		}
	}
	if (!c.start) {
		if (foundStrips2.find(c.strip) != foundStrips2.end()) {
			return true;
		}
	}
	return false;
}

bool checkHalf(state& c, queue<state>& q) {
	if (c.start) {
		if (foundStrips2.find(c.strip) != foundStrips2.end()) {
			in2 = true;
			return true;
		}
	}
	if (!c.start) {
		if (in2) {
			return false;
		}
	}
	return false;
}

void searchStates(queue<state>& strips) {
	state current = strips.front();
	int last = current.last;
	strips.pop();
	int s = current.empty;

	if (current.start) {
		bool isAns = true;
		for (int i = 1; i <= N; i++) {
			if (current.strip[i * 2 - 1] != 'W') {
				isAns = false;
				break;
			}
		}
		if (isAns) {
			for (int i = 1; i <= N; i++) {
				if (current.strip[i * 2] != 'B') {
					isAns = false;
				}
			}
			if (isAns) {
				found = true;
				ans = current;
				return;
			}
		}
	}

	if (!checkHalf(current, strips) && in2) {
		return;
	}

	if (s > 1 && last != 2) {
		if (current.strip[s - 1] != current.strip[s - 2]) {
			current.empty = s - 2;
			current.strip[s] = current.strip[s - 2];
			current.strip[s - 2] = 0;
			current.moves.push_back(s - 2);
			current.last = -2;
			if (!isDupe(current)) {
				strips.push(current);
				if (!current.start) {
					foundStrips2.insert(current.strip);
				}
				else {
					foundStrips1.insert(current.strip);
				}
			}
			current.strip[s - 2] = current.strip[s];
			current.strip[s] = 0;
			current.moves.pop_back();
		}
	}

	if (s >= 1 && last != 1) {
		current.empty = s - 1;
		current.strip[s] = current.strip[s - 1];
		current.strip[s - 1] = 0;
		current.moves.push_back(s - 1);
		current.last = -1;
		if (!isDupe(current)) {
			strips.push(current);
			if (!current.start) {
				foundStrips2.insert(current.strip);
			}
			else {
				foundStrips1.insert(current.strip);
			}
		}
		current.strip[s - 1] = current.strip[s];
		current.strip[s] = 0;
		current.moves.pop_back();
	}

	if (s < N * 2 && last != -1) {
		current.empty = s + 1;
		current.strip[s] = current.strip[s + 1];
		current.strip[s + 1] = 0;
		current.moves.push_back(s + 1);
		current.last = 1;
		if (!isDupe(current)) {
			strips.push(current);
			if (!current.start) {
				foundStrips2.insert(current.strip);
			}
			else {
				foundStrips1.insert(current.strip);
			}
		}
		current.strip[s + 1] = current.strip[s];
		current.strip[s] = 0;
		current.moves.pop_back();
	}

	if (s < N * 2 - 1 && last != -2) {
		if (current.strip[s + 1] != current.strip[s + 2]) {
			current.empty = s + 2;
			current.strip[s] = current.strip[s + 2];
			current.strip[s + 2] = 0;
			current.moves.push_back(s + 2);
			current.last = 2;
			if (!isDupe(current)) {
				strips.push(current);
				if (!current.start) {
					foundStrips2.insert(current.strip);
				}
				else {
					foundStrips1.insert(current.strip);
				}
			}
			current.strip[s + 2] = current.strip[s];
			current.strip[s] = 0;
			current.moves.pop_back();
		}
	}
}

int main() {
	ifstream fin("shuttle.in");
	fin >> N;
	state start;
	start.strip.resize(N * 2 + 1, 0);
	start.empty = N;
	start.last = 0;
	start.start = false;
	for (int i = 1; i < N; i++) {
		start.strip[i * 2 - 1] = 'W';
		start.strip[i * 2] = 'B';
	}

	/*
	queue<state> strips;
	strips.push(start);
	start.strip.clear();
	start.strip.resize(N * 2 + 1, 0);
	start.start = true;
	for (int i = 0; i < N; i++) {
		start.strip[i] = 'W';
		start.strip[start.strip.size() - i - 1] = 'B';
	}
	strips.push(start);
	while (!found) {
		searchStates(strips);
	}
	*/

	bool positive = false;
	int index = N;
	for (int i = 0; i < N; i++) {
		int m = positive ? 1 : -1;
		for (int j = 0; j < i; j++) {
			index += 2 * m;
			ans.moves.push_back(index);
		}
		index += m;
		ans.moves.push_back(index);
		positive = !positive;
	}

	int l = ans.moves.size();
	int val = N * 2;
	if (N % 2 == 1) {
		for (int i = 1; i <= N; i++) {
			ans.moves.push_back(i * 2);
		}
	}
	else {
		for (int i = N - 1; i >= 0; i--) {
			ans.moves.push_back(i * 2);
		}
	}
	for (int i = l - 2; i >= 0; i--) {
		ans.moves.push_back(val - ans.moves[i]);
	}
	ans.moves.push_back(N);

	ofstream fout("shuttle.out");
	for (int i = 0; i < ans.moves.size(); i++) {
		if (i != 0) {
			if (i % 20 == 0) {
				fout << '\n';
			}
			else {
				fout << ' ';
			}
		}
		fout << ans.moves[i] + 1;
	}
	fout << '\n';
}