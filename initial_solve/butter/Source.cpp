/*
ID: ruifanl1
TASK: butter
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

int N, P, C;
vector<int> cows;
vector<int> pastures;
vector<vector<int>> connected, paths, allDists;

struct Node {
	int no;
	int distance;
	Node(int x, int y) { no = x; distance = y; }
	bool operator<(const Node& r) const { return distance > r.distance; }
};

void dijkstra(int source) {
	vector<bool> visited(P + 1, false);
	vector<int> dist(P + 1, -1);
	priority_queue<Node> pq;

	dist[source] = 0;
	pq.push(Node(source, 0));
	while (!pq.empty()) {
		Node node = pq.top();
		int no = node.no;
		pq.pop();
		visited[no] = true;

		for (int i = 0; i < paths[no].size(); i++) {
			int nextP = paths[no][i];
			if (!visited[nextP]) {
				int nextPDist = connected[no][nextP] + node.distance;
				if (nextPDist < dist[nextP] || dist[nextP] == -1) {
					dist[nextP] = nextPDist;
				}
				pq.push(Node(nextP, dist[nextP]));
			}
		}
	}
	allDists.push_back(dist);
}

int findAns() {
	vector<int> scores(P + 1, 0);
	for (int n = 0; n < N; n++) {
		int c = cows[n];
		dijkstra(c);
	}

	for (int i = 0; i < allDists.size(); i++) {
		for (int j = 1; j <= P; j++) {
			scores[j] += allDists[i][j];
		}
	}
	int ans = -1;
	for (int i = 1; i <= P; i++) {
		int dist = scores[i];
		if (ans > dist || ans == -1) {
			ans = dist;
		}
	}

	return ans;
}

int main() {
	ifstream fin("butter.in");
	fin >> N >> P >> C;
	for (int i = 0; i < N; i++) {
		int tmp;
		fin >> tmp;
		cows.push_back(tmp);
	}
	paths.resize(P + 1);
	for (int i = 0; i <= P; i++) {
		vector<int> tmp(P + 1, -1);
		tmp[i] = 0;
		connected.push_back(tmp);
	}
	for (int i = 0; i < C; i++) {
		int p1, p2, len;
		fin >> p1 >> p2 >> len;
		paths[p1].push_back(p2);
		paths[p2].push_back(p1);
		connected[p1][p2] = len;
		connected[p2][p1] = len;
	}

	int ans = findAns();

	ofstream fout("butter.out");
	fout << ans << '\n';
}