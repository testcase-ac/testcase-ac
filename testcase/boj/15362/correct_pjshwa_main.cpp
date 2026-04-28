#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const int MAX = 1e6, MOD = 1e9 + 7;
ll mr[MAX + 1], mc[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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
  ll n, m, q;
  cin >> n >> m >> q;

  for (int i = 1; i <= n; i++) mr[i] = 1;
  for (int i = 1; i <= m; i++) mc[i] = 1;

  while (q--) {
    string s; ll x, y;
    cin >> s >> x >> y;
    if (s == "R") mr[x] = (mr[x] * y) % MOD;
    else mc[x] = (mc[x] * y) % MOD;
  }

  vector<pll> vr, vc;
  for (int i = 1; i <= n; i++) {
    if (mr[i] != 1) vr.push_back({mr[i], i});
  }
  for (int i = 1; i <= m; i++) {
    if (mc[i] != 1) vc.push_back({mc[i], i});
  }

  ll sum = 0;

  for (int i = 1; i <= n; i++) {
    ll rall = (i - 1) * m * m;
    ll csum = m * (m + 1) / 2;

    ll mul = (rall + csum) % MOD;
    mul = (mul * mr[i]) % MOD;
    sum = (sum + mul) % MOD;
  }

  for (int i = 1; i <= m; i++) {
    ll call = i * n;
    ll rsum = m * n * (n - 1) / 2;

    ll mul = (call + rsum) % MOD;
    mul = (mul * mc[i]) % MOD;
    sum = (sum + mul) % MOD;
  }

  for (auto [mr, vi] : vr) for (auto [mc, vj] : vc) {
    ll val = ((vi - 1) * m + vj) % MOD;
    ll addend = (mr * mc + MOD - mr + MOD - mc + 1) % MOD;
    addend = (addend * val) % MOD;
    sum = (sum + addend) % MOD;
  }

  ll asum = (n * m) % MOD;
  asum = asum * (asum + 1) % MOD;
  asum = asum * lpow(2, MOD - 2, MOD) % MOD;
  sum = (sum + MOD - asum) % MOD;
  cout << sum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
