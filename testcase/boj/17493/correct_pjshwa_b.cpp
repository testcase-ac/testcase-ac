#include <bits/stdc++.h>
using namespace std;

const int mx = 2e5 + 1;
const int white = 0;
const int grey = 1;
const int black = 2;

vector<int> adj[mx];
bool visited[mx];
int ans;

int dfs(int u) {
	visited[u] = true;
	int child[3] {};

	for (int& v : adj[u])
		if (!visited[v])
			++child[dfs(v)];

	if (child[white]) {
		++ans;
		return black;
	}
	if (child[black])
		return grey;
	return white;
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N, M; cin >> N >> M;
	for (int i = 0, u, v; i < M; ++i) {
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}

	for (int i = 1; i <= N; ++i)
		if (!visited[i] && !dfs(i))
			++ans;
	cout << ans;
	return 0;
}
