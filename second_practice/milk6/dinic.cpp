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

vector<Edge> es, es0;
vector<int> E[MAXN];
int levels[MAXN];
int ni[MAXN];
int N, M;

bool bfs(int s) {
	memset(levels, -1, sizeof(levels));
	levels[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		auto x = q.front();
		q.pop();
		for (auto i : E[x]) {
			auto& e = es[i];
			if (levels[e.to] < 0 && e.cap > 0) {
				levels[e.to] = levels[x] + 1;
				q.push(e.to);
			}
		}
	}
	return levels[N - 1] >= 0;
}

ll sendFlow(int v, int t, ll flow) {
	if (v == t) return flow;
	for (int& i = ni[v]; i < E[v].size(); i++) {
		auto& e = es[E[v][i]];
		if (e.cap > 0 && levels[v] + 1 == levels[e.to]) {
			ll curFlow = min(flow, e.cap);
			ll subFlow = sendFlow(e.to, t, curFlow);
			if (subFlow > 0) {
				e.cap -= subFlow;
				es[E[v][i] ^ 1].cap += subFlow;
				return subFlow;
			}
		}
	}
	return 0;
}

ll dinic() {
	int s = 0, t = N - 1;
	ll flow = 0;
	while (true) {
		if (!bfs(s)) break;;
		memset(ni, 0, sizeof(ni));
		ll newFlow;
		while ((newFlow = sendFlow(0, N - 1, inf)) > 0)
			flow += newFlow;
	}
	return flow;
}

int main() {
	fin >> N >> M;
	for (int i = 0; i < M; i++) {
		int u, v;
		ll c;
		fin >> u >> v >> c;
		u--, v--;
		c = c * (M + 1) + 1;
		int idx = es.size();
		es.push_back({ u, v, c });
		es.push_back({ v, u, 0 });
		E[u].push_back(idx);
		E[v].push_back(idx + 1);
	}
	memset(ni, 0, sizeof(ni));
	auto es0 = es;
	ll maxFlow = dinic();

	ll flow = maxFlow;
	vector<int> route;
	for (int i = 0; i < M; i++) {
		auto& e = es0[i * 2];
		ll c = e.cap;
		e.cap = 0;
		es = es0;
		ll newFlow = dinic();
		if (newFlow == flow - c) {
			route.push_back(i + 1);
			flow = newFlow;
		}
		else {
			e.cap = c;
		}
	}

	fout << maxFlow / (M + 1) << " " << route.size() << "\n";
	for (auto i : route) fout << i << "\n";
}