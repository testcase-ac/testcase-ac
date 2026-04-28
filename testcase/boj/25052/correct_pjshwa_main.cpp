#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

const int MAX = 5000, MOD = 1e9 + 7;
int P[MAX + 1], d[MAX + 1][MAX + 1];
vector<int> graph[MAX + 1];
int N;

int r(int v, int k, int p, ll acc) {
  if (d[v][k] != -1) return d[v][k];

  ll z = 0, sum = 0;
  for (int u : graph[v]) {
    if (u == p) continue;
    z++;
    sum = (sum + r(u, 1, v, P[u])) % MOD;
  }
  if (z == 0) return d[v][k] = (acc * k) % MOD;

  ll ret = 0;
  for (int u : graph[v]) {
    if (u == p) continue;

    ll pval = r(u, 1, v, P[u]);
    ll nval = r(u, k + 1, v, (acc + P[u]) % MOD);
    ret = (ret + sum + nval - pval + MOD) % MOD;
  }
  ret = (ret * lpow(z, MOD - 2, MOD)) % MOD;
  return d[v][k] = ret;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> P[i];
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  memset(d, -1, sizeof d);
  cout << r(1, 1, 0, P[1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
