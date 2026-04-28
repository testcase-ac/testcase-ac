#include <bits/stdc++.h>
using namespace std;
long long Mod = 998244353;

int n;
vector<int> adj[3010] = {};
int visited[3010] = {};
int dist[3010] = {};
int dist_set[3010][3010] = {};
int dist_sum_set[3010][3010] = {};
long long ans[3010] = {};
typedef long long ll;

ll po[3010] = {};
int r = 0;
void set_po(void) {
	po[0] = 1;
	for (int i = 1; i <= 3000; i++) {
		po[i] = (po[i - 1] * 2LL) % Mod;
	}
	return;
}
void f(int d) {
	int nd = 0;
	int ndd = 0;
	for (int u = 1; u <= r; u++) {
		nd += dist_sum_set[u][d];
		ndd += dist_sum_set[u][d - 1];
	}
	ll re = 0;
	re = po[nd + 1] - po[ndd + 1];
	for (int u = 1; u <= r; u++) {
		re -= ((po[dist_set[u][d]] - 1LL) * po[ndd + 1]) % Mod;
		re = (re + Mod) % Mod;
	}
	ans[2 * d] += re;
}

void g(int d) {
	int nd = 0;
	int ndd = 0;
	for (int u = 1; u <= r; u++) {
		nd += dist_sum_set[u][d];
		ndd += dist_sum_set[u][d - 1];
	}
	ll re = 0;
	for (int u = 1; u <= r; u++) {
		ll p = 0;
		if ((dist_set[u][d + 1] == -1) || (dist_set[u][d + 1] == 0)) continue;
		re += ((po[dist_set[u][d + 1]] - 1LL) * (po[nd + 1] - po[dist_set[u][d] + ndd + 1])) % Mod;
	}
	ans[2 * d + 1] += re;
}

void sol(int i) {
	memset(visited, -1, sizeof(visited));
	memset(dist, -1, sizeof(dist));
	memset(dist_set, 0, sizeof(dist_set));
	memset(dist_sum_set, 0, sizeof(dist_sum_set));
	r = 0;
	queue<int> qu;
	visited[i] = 0;
	dist[i] = 0;
	for (auto x : adj[i]) {
		visited[x] = ++r;
		dist[x] = 1;
		qu.push(x);
		dist_set[r][1]++;
	}
	if (r == 1) return;
	int M = 1;
	while (!qu.empty()) {
		int t = qu.front();
		qu.pop();
		for (auto n : adj[t]) {
			if (visited[n] != -1) continue;
			visited[n] = visited[t];
			dist[n] = dist[t] + 1;
			M = max(M, dist[n]);
			dist_set[visited[n]][dist[n]]++;
			qu.push(n);
		}
	}

	for (int u = 1; u <= r; u++) {
		dist_sum_set[u][1] = dist_set[u][1];
		for (int k = 2; k <= M; k++) {
			dist_sum_set[u][k] = dist_sum_set[u][k - 1] + dist_set[u][k];
		}
	}

	int d = 0;
	for (d = 1; d <= M; d++) {
		f(d);
		g(d);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	set_po();
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	ans[0] = n;
	ans[1] = n - 1;
	for (int i = 1; i <= n; i++) {
		sol(i);
	}
	for (int i = 0; i <= n - 1; i++) {
		if ((i % 2 == 1) && (i != 1)) ans[i] /= 2;
		cout << ans[i] << " ";
	}
}
