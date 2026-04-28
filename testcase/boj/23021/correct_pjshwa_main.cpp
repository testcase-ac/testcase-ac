#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20, MOD = 1e9 + 7;
ll fac[MAX];
ll A[MAX], B[MAX];

void solve() {
  int n, m, x, C, D;
  cin >> n >> m >> x >> C >> D;
  for (int i = 0; i < n; i++) cin >> A[i];
  for (int i = 0; i < m; i++) cin >> B[i];

  vector<ll> ac[n + 1];
  for (int i = 0; i < (1 << n); i++) {
    int z = __builtin_popcount(i);
    ll sum = 0;
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) sum += A[j];
    }
    ac[z].push_back(sum);
  }
  for (int i = 0; i <= n; i++) sort(ac[i].begin(), ac[i].end());

  ll ans = 0;
  for (int i = 0; i < (1 << m); i++) {
    int z = __builtin_popcount(i);
    ll sum = 0;
    for (int j = 0; j < m; j++) {
      if (i & (1 << j)) sum += B[j];
    }

    for (int k : {z - 1, z, z + 1}) {
      if (k < 0 || k > n || z + k <= 0) continue;
      ll bcost = (ll)(z + k - 1) * x;
      ll ub = D - (sum + bcost), lb = C - (sum + bcost);
      auto uit = upper_bound(ac[k].begin(), ac[k].end(), ub);
      auto lit = lower_bound(ac[k].begin(), ac[k].end(), lb);

      ll cur = fac[z], w = uit - lit;
      cur = (cur * w) % MOD;
      cur = (cur * fac[k]) % MOD;
      if (z == k) cur = (cur * 2) % MOD;

      ans = (ans + cur) % MOD;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = 1;
  for (int i = 1; i < MAX; i++) fac[i] = fac[i - 1] * i % MOD;

  int t = 1;
  cin >> t;
  while (t--) solve();
}
