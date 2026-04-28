#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
ll A[MAX + 1], ssz[MAX + 1], usz[MAX + 1];
vector<int> graph[MAX + 1];
ll Z;
vector<tll> ops;

void dfs1(int v, int p) {
  ssz[v] = 1;
  usz[v] = A[v];
  for (int u : graph[v]) {
    if (u == p) continue;
    dfs1(u, v);
    ssz[v] += ssz[u];
    usz[v] += usz[u];
  }
}

void dfs2_o(int v, int p) {
  for (int u : graph[v]) {
    if (u == p) continue;

    dfs2_o(u, v);
    if (usz[u] > ssz[u] * Z) ops.push_back({u, v, usz[u] - ssz[u] * Z});
  }
}

void dfs2_u(int v, int p) {
  for (int u : graph[v]) {
    if (u == p) continue;

    if (usz[u] < ssz[u] * Z) ops.push_back({v, u, ssz[u] * Z - usz[u]});
    dfs2_u(u, v);
  }
}

void solve() {
  int N;
  cin >> N;

  ll sum = 0;
  for (int i = 1; i <= N; i++) cin >> A[i], sum += A[i];
  Z = sum / N;

  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  dfs1(1, -1);
  dfs2_o(1, -1);
  dfs2_u(1, -1);

  cout << ops.size() << '\n';
  for (auto [u, v, z] : ops) cout << u << ' ' << v << ' ' << z << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
