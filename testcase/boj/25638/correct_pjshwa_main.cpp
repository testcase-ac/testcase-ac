#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
int N, C[MAX + 1], ssz[MAX + 1], rsz[MAX + 1], tsz;
ll d[MAX + 1];

void dfs1(int v, int p) {
  ssz[v] = 1;
  rsz[v] = C[v];
  for (int u : graph[v]) {
    if (u == p) continue;

    dfs1(u, v);
    ssz[v] += ssz[u];
    rsz[v] += rsz[u];
  }
}

void dfs2(int v, int p) {
  for (int u : graph[v]) {
    if (u == p) continue;

    dfs2(u, v);

    ll bsz_u = ssz[u] - rsz[u];
    ll rsz_a = tsz - rsz[u] - (C[v] == 1);
    ll bsz_a = (N - tsz) - bsz_u - (C[v] == 0);
    d[v] += rsz[u] * bsz_a + rsz_a * bsz_u;
    d[v] += rsz[u] * bsz_u;
  }

  ll rsz_sub = rsz[v] - (C[v] == 1);
  ll bsz_sub = ssz[v] - rsz[v] - (C[v] == 0);
  d[v] -= rsz_sub * bsz_sub;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> C[i], tsz += C[i];
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  dfs1(1, -1);
  dfs2(1, -1);

  int Q; cin >> Q;
  while (Q--) {
    int v; cin >> v;
    cout << d[v] << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
