#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;

const int MAX = 5000, MOD = 1e9 + 7;
vector<pii> graph[MAX + 1];
bool vis[MAX + 1];
ll fac[MAX + 1], ifac[MAX + 1];
ll ans = 0;
int n, m;

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
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

int dfs(int v) {
  vis[v] = true;

  int ret = 0;
  for (auto [w, u] : graph[v]) {
    if (!vis[u]) {
      int res = dfs(u);
      for (int i = 1; i <= 2 * m; i++) {
        ll mul = C(2 * m, i);
        mul = mul * lpow(res, i, MOD) % MOD;
        mul = mul * lpow(n - res, 2 * m - i, MOD) % MOD;
        mul = mul * w % MOD;
        mul = mul * min(i, 2 * m - i) % MOD;
        ans = (ans + mul) % MOD;
      }
      ret += res;
    }
  }
  return ret + 1;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({w, v});
    graph[v].push_back({w, u});
  }

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX] = lpow(fac[MAX], MOD - 2, MOD);
  for (int i = MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  dfs(1);
  cout << ans << '\n';
}
