#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
int MOD;
vector<int> adj[MAXN + 1];

// (node, color, parent_color)
ll dp[MAXN + 1][2][2];

ll dfs(int v, int c, int pc, int p) {
  if (dp[v][c][pc] != -1) return dp[v][c][pc];

  vector<ll> PL, PR;
  for (int u : adj[v]) {
    if (u == p) continue;
    PL.push_back(dfs(u, c, c, v));
  }
  PR = PL; int Z = PL.size();
  for (int i = 1; i < Z; ++i) {
    PL[i] = (PL[i - 1] * PL[i]) % MOD;
    PR[Z - i - 1] = (PR[Z - i] * PR[Z - i - 1]) % MOD;
  }
  if (Z == 0) return dp[v][c][pc] = 1;

  ll res = PL.back();
  if (v == 1 || c == pc) {
    int i = 0;
    for (int u : adj[v]) {
      if (u == p) continue;
      ll cur = dfs(u, 1 - c, c, v);
      cur = (cur * (i == 0 ? 1LL : PL[i - 1])) % MOD;
      cur = (cur * (i == Z - 1 ? 1LL : PR[i + 1])) % MOD;
      res = (res + cur) % MOD;
      ++i;
    }
  }
  return dp[v][c][pc] = res;
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

void solve() {
  int N; cin >> N >> MOD;
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  ll tot = lpow(2, N, MOD), cnt = 0;

  memset(dp, -1, sizeof(dp));
  cnt = (cnt + dfs(1, 0, 0, 0)) % MOD;
  cnt = (cnt + dfs(1, 1, 0, 0)) % MOD;

  ll ans = (tot - cnt + MOD) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
