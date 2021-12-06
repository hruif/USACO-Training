/*
ID: ruifanl1
TASK: fence6
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> endPoints, allDists;

int existsAlready(vector<int>& end) {
	int a = end[0];
	int b = end[1];
	bool hasA = false;
	bool hasB = false;
	int len = endPoints.size();
	for (int i = 0; i < len; i++) {
		int endLen = endPoints[i].size();
		for (int j = 0; j < endLen; j++) {
			if (endPoints[i][j] == a) {
				hasA = true;
			}
			if (endPoints[i][j] == b) {
				hasB = true;
			}
			if (hasA && hasB) {
				return i;
			}
		}
		hasA = false;
		hasB = false;
	}
	return -1;
}

int findPerimeter(int source) {
	vector<bool> visited(N, false), loopedOn(N, false);
	vector<int> dists(N, -1);
	vector<int> perimDists(N, -1);
	vector<int> parents(N, -1);
	dists[source] = 0;
	parents[source] = -1;
	while (true) {
		int distLen = dists.size();
		int closest, closestDist = -1;
		for (int i = 0; i < distLen; i++) {
			int dist = dists[i];
			if (visited[i]) {
				if (!loopedOn[i]) {
					continue;
				}
				else {
					int perimDist = perimDists[i];
					if (perimDist <= closestDist || closestDist == -1) {
						closestDist = perimDist;
						closest = i;
					}
				}
			}
			else if (dist != -1) {
				if (dist < closestDist || closestDist == -1) {
					closestDist = dist;
					closest = i;
				}
			}
		}

		if (visited[closest]) {
			return perimDists[closest];
		}
		visited[closest] = true;
		int len = endPoints[closest].size();
		for (int i = 0; i < len; i++) {
			int next = endPoints[closest][i];
			int nextDist = allDists[closest][next] + dists[closest];
			if (next == parents[closest]) {
				continue;
			}
			if ((nextDist < dists[next] || dists[next] == -1) && !visited[next]) {
				dists[next] = nextDist;
				parents[next] = closest;
			}
			if (visited[next]) {
				int perimeter = dists[next] + nextDist;
				int perimDist = perimDists[next];
				if (perimeter < perimDist || perimDist == -1) {
					perimDists[next] = perimeter;
					loopedOn[next] = true;
				}
			}
		}
	}
}

int findAns() {
	int ans = -1;
	int len = endPoints.size();
	for (int i = 0; i < len; i++) {
		int perimeter = findPerimeter(i);
		if (perimeter < ans || ans == -1) {
			ans = perimeter;
		}
	}
	return ans;
}

void showPoints() {
	int len = endPoints.size();
	vector<vector<int>> newArray(len);
	for (int i = 0; i < len; i++) {
		int endLen = endPoints[i].size();
		for (int j = 0; j < endLen; j++) {
			int fence = endPoints[i][j];
			int found = false;
			for (int k = 0; k < len; k++) {
				if (k == i) {
					continue;
				}
				int nextEndLen = endPoints[k].size();
				for (int l = 0; l < nextEndLen; l++) {
					if (endPoints[k][l] == fence) {
						found = true;
						newArray[i].push_back(k);
						break;
					}
				}
				if (found) {
					break;
				}
			}
		}
	}
	endPoints = newArray;
}

int main() {
	ifstream fin("fence6.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int s, L, N1, N2;
		fin >> s >> L >> N1 >> N2;
		vector<int> end1, end2;
		s--;
		end1.push_back(s);
		end2.push_back(s);
		for (int j = 0; j < N1; j++) {
			int tmp;
			fin >> tmp;
			tmp--;
			end1.push_back(tmp);
		}
		for (int j = 0; j < N2; j++) {
			int tmp;
			fin >> tmp;
			tmp--;
			end2.push_back(tmp);
		}

		int a, b;

		int existingEnd = existsAlready(end1);
		if (existingEnd == -1) {
			endPoints.push_back(end1);
			a = endPoints.size() - 1;
		}
		else {
			a = existingEnd;
		}
		existingEnd = existsAlready(end2);
		if (existingEnd == -1) {
			endPoints.push_back(end2);
			b = endPoints.size() - 1;
		}
		else {
			b = existingEnd;
		}

		int max = a > b ? a : b;
		for (int j = allDists.size(); j <= max; j++) {
			allDists.push_back(vector<int>(max, -1));
		}
		int aSize = allDists[a].size();
		for (int j = aSize; j <= max; j++) {
			allDists[a].push_back(-1);
		}
		int bSize = allDists[b].size();
		for (int j = bSize; j <= max; j++) {
			allDists[b].push_back(-1);
		}
		allDists[a][b] = L;
		allDists[b][a] = L;
	}

	showPoints(); // convert endpoints array from showing connected fences to connected points
	int ans = findAns();

	ofstream fout("fence6.out");
	fout << ans << '\n';
}