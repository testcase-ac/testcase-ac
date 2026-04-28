#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
vector<int> adj[MAXN + 1];
ld S[MAXN + 1], P[MAXN + 1];

void dfs1(int v) {
  S[v] = 1;
  for (int u : adj[v]) {
    dfs1(u);
    S[v] += S[u];
  }
}

void dfs2(int v) {
  if (adj[v].empty()) P[v] = 1;
  else {
    for (int u : adj[v]) {
      dfs2(u);
      P[v] = max(P[v], min(P[u], S[u] / (S[v] - 1)));
    }
  }
}

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 2; i <= N; i++) {
    int p; cin >> p;
    adj[p].push_back(i);
  }
  dfs1(1);
  dfs2(1);

  ld ans = 0;
  for (int i = 1; i <= N; ++i) {
    if (S[i] > K) ans = max(ans, P[i]);
  }
  cout << fixed << setprecision(9) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
