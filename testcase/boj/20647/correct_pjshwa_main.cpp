#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
ll indegree[MAX + 1], d[MAX + 1];

ll r(int v, int p) {
  if (d[v] != -1) return d[v];

  ll ret = 0, val = 1;
  int c = indegree[v];
  if (v == 1) c++;
  while (val < c) {
    ret++;
    val *= 2;
  }

  for (int u : graph[v]) {
    if (u == p) continue;
    ret += r(u, v) + 1;
  }
  return d[v] = ret;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
    indegree[u]++;
    indegree[v]++;
  }

  memset(d, -1, sizeof(d));
  cout << r(1, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
