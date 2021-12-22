/*
ID: ruifanl1
TASK: milk6
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>
#include <string.h>
#include <queue>
#include <tuple>

using namespace std;
using ll = long long;
ll inf = 1e18;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

ifstream fin("milk6.in");
ofstream fout("milk6.out");

struct Edge {
	int from, to;
	ll cap;
};

const int MAXN = 35;

int N, M;
vector<Edge> es;
vector<int> edges[MAXN];
int levels[MAXN];
//int ni[MAXN];

bool bfs(int source, int sink) {
	memset(levels, -1, sizeof(levels));

	queue<int> q;
	levels[source] = 0;
	q.push(source);
	while (!q.empty()) {
		int node = q.front();
		q.pop();

		for (auto x : edges[node]) {
			Edge& e = es[x];
			if (levels[e.to] < 0 && e.cap > 0) {
				levels[e.to] = levels[node] + 1;
				q.push(e.to);
			}
		}
	}
	return levels[sink] >= 0;
}

ll sendFlow(int cur, int sink, ll flow) {
	if (cur == sink) return flow;

	for (int i = 0; i < edges[cur].size(); i++) {
		Edge& e = es[edges[cur][i]];

		if (e.cap > 0 && levels[e.to] == levels[cur] + 1) {
			ll sub_flow = sendFlow(e.to, sink, min(flow, e.cap));
			if (sub_flow > 0) {
				e.cap -= sub_flow;
				es[edges[cur][i] ^ 1].cap += sub_flow;
				return sub_flow;
			}
		}
	}
	return 0;
}

ll dinic() {
	ll flow = 0;
	const int source = 0, sink = N - 1;
	while (true) {
		if (!bfs(source, sink)) break;

		//memset(ni, 0, sizeof(ni));

		ll new_flow;
		while ((new_flow = sendFlow(source, sink, inf)) > 0) {
			flow += new_flow;
		}
	}
	return flow;
}

int main() {
	fin >> N >> M;
	for (int i = 0; i < M; i++) {
		int S, E;
		ll C;
		fin >> S >> E >> C;
		S--; E--;
		C = C * (M + 1) + 1;
		edges[S].push_back(es.size());
		es.push_back({ S, E, C });
		edges[E].push_back(es.size());
		es.push_back({ E, S, 0 });
	}
	auto es0 = es;

	//memset(ni, 0, sizeof(ni));
	ll max_flow = dinic();

	ll flow = max_flow;
	vector<int> cut;
	for (int i = 0; i < M; i++) {
		Edge& e = es0[i * 2];

		ll cap = e.cap;
		e.cap = 0;

		es = es0;
		ll new_flow = dinic();
		if (new_flow == flow - cap) {
			cut.push_back(i + 1);
			flow = new_flow;
		}
		else e.cap = cap;
	}
	fout << max_flow / (M + 1) << ' ' << cut.size() << '\n';
	for (auto x : cut) fout << x << '\n';
}