#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e5, MOD = 1e9 + 7;
int deg[MAXV + 1];

int nC3(int n) {
  if (n < 3) return 0;
  return (ll)n * (n - 1) % MOD * (n - 2) % MOD * 166666668 % MOD;
}

void solve() {
  int n, m; cin >> n >> m;
  while (m--) {
    int u, v; cin >> u >> v;
    deg[u]++; deg[v]++;
  }

  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans = (ans + nC3(deg[i])) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
