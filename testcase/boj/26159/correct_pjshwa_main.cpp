#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 7;
vector<pii> graph[MAX + 1];
ll A[MAX + 1], E[MAX + 1], ssz[MAX + 1];

void dfs1(int v, int p) {
  ssz[v] = 1;
  for (auto [u, _] : graph[v]) {
    if (u == p) continue;
    dfs1(u, v);
    ssz[v] += ssz[u];
  }
}

void dfs2(int v, int p) {
  for (auto [u, i] : graph[v]) {
    if (u == p) continue;
    E[i] += ssz[u] * (ssz[1] - ssz[u]);
    dfs2(u, v);
  }
}

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].emplace_back(v, i);
    graph[v].emplace_back(u, i);
  }

  dfs1(1, 0);
  dfs2(1, 0);

  for (int i = 1; i <= N - 1; i++) cin >> A[i];
  sort(A + 1, A + N);
  sort(E + 1, E + N);
  reverse(E + 1, E + N);

  ll ans = 0;
  for (int i = 1; i <= N - 1; i++) {
    ans = (ans + A[i] * E[i]) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
