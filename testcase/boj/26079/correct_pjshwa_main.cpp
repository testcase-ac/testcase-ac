#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 4e5, MOD = 1e9 + 7;
vector<int> graph[MAX + 1];
int indegree[MAX + 1], ssz[MAX + 1];
ll fac[MAX + 1], ifac[MAX + 1];

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

void dfs(int v) {
  ssz[v] = 1;
  for (int u : graph[v]) {
    dfs(u);
    ssz[v] += ssz[u];
  }
}

ll r(int v) {
  int tsz = ssz[v] - 1;
  ll ret = fac[tsz];
  for (int u : graph[v]) {
    ret = ret * ifac[ssz[u]] % MOD;
    ret = ret * r(u) % MOD;
  }
  return ret;
}

void solve() {
  int N, M;
  cin >> N >> M;
  while (M--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    indegree[v]++;
  }

  for (int i = 1; i <= N; i++) {
    if (indegree[i] == 0) graph[0].push_back(i);
  }

  dfs(0);
  cout << r(0) << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX] = lpow(fac[MAX], MOD - 2, MOD);
  for (int i = MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
