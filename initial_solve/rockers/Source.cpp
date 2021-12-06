/*
ID: ruifanl1
TASK: rockers
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int N, T, M;
vector<int> songs;
vector<vector<int>> nextPossible;

void deleteDuplicates(vector<int>& a) {
	for (int i = 0; i < a.size(); i++) {
		int og = songs[a[i]];
		for (int j = 0; j < a.size(); j++) {
			if (i == j) {
				continue;
			}
			if (songs[a[j]] == og) {
				a.erase(a.begin() + j);
				j--;
			}
		}
	}
}

int checkSongs(queue<vector<int>>& nextSongs) {
	vector<int> chosen = nextSongs.front();
	nextSongs.pop();

	int min = 0, disks = 1;
	for (int i = 1; i < chosen.size(); i++) {
		int songSize = songs[chosen[i] - 1];
		if (min + songSize > T) {
			disks++;
			min = songSize;
		}
		else {
			min += songSize;
		}
	}

	int last = chosen[chosen.size() - 1];
	for (int i = 0; i < nextPossible[last].size(); i++) {
		int next = nextPossible[last][i];
		if (disks < M || songs[next] + min <= T) {
			chosen.push_back(next + 1);
			nextSongs.push(chosen);
			chosen.pop_back();
		}
	}
	return chosen.size() - 1;
}

int findAns() {
	queue<vector<int>> nextSongs;
	vector<int> noSongs(1, 0);
	nextSongs.push(noSongs);

	int ans = -1;
	while (!nextSongs.empty()) {
		int numSongs = checkSongs(nextSongs);
		if (numSongs > ans) {
			ans = numSongs;
		}
	}
	return ans;
}

int main() {
	ifstream fin("rockers.in");
	fin >> N >> T >> M;

	nextPossible.resize(1);
	for (int i = 0; i < N; i++) {
		nextPossible[0].push_back(i);
	}
	for (int i = 0; i < N; i++) {
		int song;
		fin >> song;
		if (song > T) {
			continue;
		}
		vector<int> possibleFromI;
		for (int j = i + 1; j < N; j++) {
			possibleFromI.push_back(j);
		}
		nextPossible.push_back(possibleFromI);
		songs.push_back(song);
	}

	int ans = 0;
	if (songs.size() > 0) {
		for (int i = 0; i < nextPossible.size(); i++) {
			deleteDuplicates(nextPossible[i]);
		}

		ans = findAns();
	}

	ofstream fout("rockers.out");
	fout << ans << '\n';
}