#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 7;
ll A[MAX + 1], U[MAX + 1], P[MAX + 1];
vector<pii> adj[MAX + 1];
int ans;

void dfs1(int v) {
  U[v] = 1;
  for (auto [u, w] : adj[v]) {
    P[u] = P[v] + w;
    dfs1(u);
    U[v] += U[u];
  }
}

void dfs2(int v) {
  if (P[v] > A[v]) return ans += U[v], void();
  for (auto [u, _] : adj[v]) dfs2(u);
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 2; i <= N; i++) {
    int p, w; cin >> p >> w;
    adj[p].emplace_back(i, w);
  }

  dfs1(1); dfs2(1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
