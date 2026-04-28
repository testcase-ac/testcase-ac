#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50000;
vector<pii> graph[MAX + 1];
int d1[MAX + 1], d2[MAX + 1];

int dfs1(int v, int p) {
  int res = 0;
  for (auto& [u, dis] : graph[v]) {
    if (u == p) continue;
    res = max(res, dfs1(u, v) + dis);
  }
  return d1[v] = res;
}

void dfs2(int v, int p, int tdis) {
  priority_queue<int, vector<int>, greater<int>> top2;
  for (auto& [u, dis] : graph[v]) {
    if (u == p) continue;
    top2.push(d1[u] + dis);
    if (top2.size() > 2) top2.pop();
  }

  d2[v] = max(d1[v], tdis);

  int vals[2] = {0, 0};
  for (int i = 0; i < 2; i++) {
    if (top2.empty()) break;
    vals[i] = top2.top();
    top2.pop();
  }
  if (vals[1] != 0) swap(vals[0], vals[1]);

  for (auto& [u, dis] : graph[v]) {
    if (u == p) continue;

    if (d1[u] + dis == vals[0]) dfs2(u, v, max(tdis, vals[1]) + dis);
    else dfs2(u, v, max(tdis, vals[0]) + dis);
  }

}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int u, v, d;
    cin >> u >> v >> d;
    graph[u].push_back({v, d});
    graph[v].push_back({u, d});
  }
  dfs1(1, -1);
  dfs2(1, -1, 0);

  for (int i = 1; i <= N; i++) cout << d2[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
