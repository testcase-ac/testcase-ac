#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 200, MAXK = 10, MOD = 93563;
int d[MAX + 1][MAXK + 1];
vector<int> graph[MAX + 1];
int K;

int r(int v, int p, int c) {
  if (d[v][c] != -1) return d[v][c];

  int ret = 1;
  for (int u : graph[v]) {
    if (u == p) continue;

    int mul = 0;
    for (int nc = 1; nc <= K; nc++) {
      if (nc == c) continue;
      mul = (mul + r(u, v, nc)) % MOD;
    }
    ret = (ret * mul) % MOD;
  }

  return d[v][c] = ret;
}

void solve() {
  int N; cin >> N >> K;
  for (int i = 1; i <= N; i++) graph[i].clear();
  for (int i = 1; i <= N - 1; i++) {
    int u, v; cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  memset(d, -1, sizeof(d));
  int ans = 0;
  for (int i = 1; i <= K; i++) ans = (ans + r(1, -1, i)) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
