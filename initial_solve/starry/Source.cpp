/*
ID: ruifanl1
TASK: starry
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

struct cluster {
	vector<vector<bool>> clust;
	cluster(int w, int h) {
		clust.resize(h, vector<bool>(w, false));
	}
};

int W, H;
vector<vector<bool>> sky; // the sky indicating where the stars are
vector<vector<int>> clustsInSky; // the sky with each cluster numbered
vector<cluster> clusters; // shapes of all clusters

void pointsToCluster(vector<pair<int, int>>& points) {
	int top, bot, left, right;
	top = bot = left = right = -1;
	for (int i = 0; i < points.size(); i++) {
		if (points[i].first < left || left == -1) {
			left = points[i].first;
		}
		if (points[i].first > right) {
			right = points[i].first;
		}
		if (points[i].second < top || top == -1) {
			top = points[i].second;
		}
		if (points[i].second > bot) {
			bot = points[i].second;
		}
	}
	int w = right - left + 1;
	int h = bot - top + 1;
	cluster current(w, h);
	for (int i = 0; i < points.size(); i++) {
		current.clust[points[i].second - top][points[i].first - left] = true;
	}
	clusters.push_back(current);
}

void findCluster(vector<vector<bool>>& visited, int x, int y, int clustNum) {
	vector<pair<int, int>> clustPoints;
	queue<pair<int, int>> nextStars;
	pair<int, int> start(x, y);
	nextStars.push(start);
	clustPoints.push_back(start);
	clustsInSky[y][x] = clustNum;
	while (!nextStars.empty()) {
		pair<int, int> current = nextStars.front();
		nextStars.pop();

		int f = current.first;
		int s = current.second;
		if (f > 0) {
			if (s > 0) {
				if (!visited[s - 1][f - 1] && sky[s - 1][f - 1]) {
					clustsInSky[s - 1][f - 1] = clustNum;
					pair<int, int> next(f - 1, s - 1);
					clustPoints.push_back(next);
					nextStars.push(next);
				}
				visited[s - 1][f - 1] = true;
			}
			if (s < H - 1) {
				if (!visited[s + 1][f - 1] && sky[s + 1][f - 1]) {
					clustsInSky[s + 1][f - 1] = clustNum;
					pair<int, int> next(f - 1, s + 1);
					clustPoints.push_back(next);
					nextStars.push(next);
				}
				visited[s + 1][f - 1] = true;
			}
			if (!visited[s][f - 1] && sky[s][f - 1]) {
				clustsInSky[s][f - 1] = clustNum;
				pair<int, int> next(f - 1, s);
				clustPoints.push_back(next);
				nextStars.push(next);
			}
			visited[s][f - 1] = true;
		}

		if (f < W - 1) {
			if (s > 0) {
				if (!visited[s - 1][f + 1] && sky[s - 1][f + 1]) {
					clustsInSky[s - 1][f + 1] = clustNum;
					pair<int, int> next(f + 1, s - 1);
					clustPoints.push_back(next);
					nextStars.push(next);
				}
				visited[s - 1][f + 1] = true;
			}
			if (s < H - 1) {
				if (!visited[s + 1][f + 1] && sky[s + 1][f + 1]) {
					clustsInSky[s + 1][f + 1] = clustNum;
					pair<int, int> next(f + 1, s + 1);
					clustPoints.push_back(next);
					nextStars.push(next);
				}
				visited[s + 1][f + 1] = true;
			}
			if (!visited[s][f + 1] && sky[s][f + 1]) {
				clustsInSky[s][f + 1] = clustNum;
				pair<int, int> next(f + 1, s);
				clustPoints.push_back(next);
				nextStars.push(next);
			}
			visited[s][f + 1] = true;
		}

		if (s > 0) {
			if (!visited[s - 1][f] && sky[s - 1][f]) {
				clustsInSky[s - 1][f] = clustNum;
				pair<int, int> next(f, s - 1);
				clustPoints.push_back(next);
				nextStars.push(next);
			}
			visited[s - 1][f] = true;
		}
		
		if (s < H - 1) {
			if (!visited[s + 1][f] && sky[s + 1][f]) {
				clustsInSky[s + 1][f] = clustNum;
				pair<int, int> next(f, s + 1);
				clustPoints.push_back(next);
				nextStars.push(next);
			}
			visited[s + 1][f] = true;
		}
	}
	pointsToCluster(clustPoints);
}

bool compareClusters(int a, int b) {
	int aW = clusters[a].clust[0].size();
	int aH = clusters[a].clust.size();
	int bW = clusters[b].clust[0].size();
	int bH = clusters[b].clust.size();
	if (aW != bW || aH != bH) {
		if (aW != bH || aH != bW) {
			return false;
		}
	}

	bool similar = true;
	if (aW == bW) { // same w x h (a = w x h, b = w x h)
		for (int i = 0; i < aH; i++) { // same orientation
			for (int j = 0; j < aW; j++) {
				if (clusters[a].clust[i][j] != clusters[b].clust[i][j]) {
					similar = false;
					break;
				}
			}
			if (!similar) {
				break;
			}
		}
		if (similar) {
			return true;
		}

		similar = true;
		for (int i = 0; i < aH; i++) { // rotated 180
			for (int j = 0; j < aW; j++) {
				if (clusters[a].clust[i][j] != clusters[b].clust[bH - i - 1][bW - j - 1]) {
					similar = false;
					break;
				}
			}
			if (!similar) {
				break;
			}
		}
		if (similar) {
			return true;
		}

		similar = true;
		for (int i = 0; i < aH; i++) { // flipped horizontally
			for (int j = 0; j < aW; j++) {
				if (clusters[a].clust[i][j] != clusters[b].clust[i][bW - j - 1]) {
					similar = false;
					break;
				}
			}
			if (!similar) {
				break;
			}
		}
		if (similar) {
			return true;
		}

		similar = true;
		for (int i = 0; i < aH; i++) { // rotated & flipped (same as flipped vertically)
			for (int j = 0; j < aW; j++) {
				if (clusters[a].clust[i][j] != clusters[b].clust[bH - i - 1][j]) {
					similar = false;
					break;
				}
			}
			if (!similar) {
				break;
			}
		}
		if (similar) {
			return true;
		}
	}
	similar = true;
	if (aW == bH) { // flipped w x h (a = w x h, b = h x w)
		for (int i = 0; i < aH; i++) { // rotated 90
			for (int j = 0; j < aW; j++) {
				if (clusters[a].clust[i][j] != clusters[b].clust[j][bW - i - 1]) {
					similar = false;
					break;
				}
			}
			if (!similar) {
				break;
			}
		}
		if (similar) {
			return true;
		}

		similar = true;
		for (int i = 0; i < aH; i++) { // rotated 270
			for (int j = 0; j < aW; j++) {
				if (clusters[a].clust[i][j] != clusters[b].clust[bH - j - 1][i]) {
					similar = false;
					break;
				}
			}
			if (!similar) {
				break;
			}
		}
		if (similar) {
			return true;
		}

		similar = true;
		for (int i = 0; i < aH; i++) { // rotated 90 flipped horizontally
			for (int j = 0; j < aW; j++) {
				if (clusters[a].clust[i][j] != clusters[b].clust[j][i]) {
					similar = false;
					break;
				}
			}
			if (!similar) {
				break;
			}
		}
		if (similar) {
			return true;
		}

		similar = true;
		for (int i = 0; i < aH; i++) { // rotate 270 & flipped
			for (int j = 0; j < aW; j++) {
				if (clusters[a].clust[i][j] != clusters[b].clust[bH - j - 1][bW - i - 1]) {
					similar = false;
					break;
				}
			}
			if (!similar) {
				break;
			}
		}
		if (similar) {
			return true;
		}
	}
	return false;
}

int main() {
	ifstream fin("starry.in");
	fin >> W >> H;
	for (int i = 0; i < H; i++) {
		vector<bool> row;
		for (int j = 0; j < W; j++) {
			char tmp;
			fin >> tmp;
			if (tmp == '1') {
				row.push_back(true);
			}
			else {
				row.push_back(false);
			}
		}
		sky.push_back(row);
	}

	vector<vector<bool>> visited(H, vector<bool>(W, false));
	clustsInSky.resize(H, vector<int>(W, 0));
	int numOfClusters = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (visited[i][j] || !sky[i][j]) {
				continue;
			}
			numOfClusters++;
			visited[i][j] = true;
			findCluster(visited, j, i, numOfClusters);
		}
	}

	vector<int> clusterNums(numOfClusters, -1); // nums to represent clusters - similar clusters will have same num
	int unique = 1;
	clusterNums[0] = 1;
	for (int i = 1; i <= numOfClusters; i++) {
		if (clusterNums[i - 1] == -1) {
			unique++;
			clusterNums[i - 1] = unique;
		}
		for (int j = i + 1; j <= numOfClusters; j++) {
			if (clusterNums[j - 1] != -1) {
				continue;
			}
			if (compareClusters(i - 1, j - 1)) {
				clusterNums[j - 1] = clusterNums[i - 1];
			}
		}
	}
	char v = 26 + 'a';

	ofstream fout("starry.out");
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			int clust = clustsInSky[i][j];
			if (clust == 0) {
				fout << 0;
			}
			else {
				char letter = clusterNums[clust - 1] - 1 + 'a';
				fout << letter;
			}
		}
		fout << '\n';
	}
}