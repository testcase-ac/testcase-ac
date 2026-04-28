#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll NOM = 26771144400LL;
const int MAXN = 1e5, MAXV = 25, MOD = 1e9 + 7, CUT = 18;
int t[MAXV + 1];
ll fac[MAXN + 1], ifac[MAXN + 1];

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

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

vector<int> cur(20);
ll sum = 0, ans = 0;
map<ll, ll> c;

void dfs1(int i) {
  if (sum > 27038855844LL) return;

  for (int j = i; j <= CUT; j++) {
    cur[j]++;
    sum += NOM / j;
    dfs1(j);
    cur[j]--;
    sum -= NOM / j;
  }

  ll val = 1;
  for (int i = 1; i <= CUT; i++) val = (val * C(t[i], cur[i])) % MOD;
  c[sum] = (c[sum] + val) % MOD;
}

void dfs2(int i) {
  if (sum > 27038855844LL) return;

  for (int j = i; j <= MAXV - CUT; j++) {
    cur[j]++;
    sum += NOM / (j + CUT);
    dfs2(j);
    cur[j]--;
    sum -= NOM / (j + CUT);
  }

  ll val = 1;
  for (int i = 1; i <= MAXV - CUT; i++) val = (val * C(t[i + CUT], cur[i])) % MOD;
  if (val == 0) return;

  ll lb = 26503432956LL - sum, ub = 27038855844LL - sum;
  auto lit = c.lower_bound(lb), uit = c.upper_bound(ub);
  if (uit == c.begin()) return;
  uit--;

  ll lft;
  if (lit == c.begin()) lft = 0;
  else {
    lit--;
    lft = lit->second;
  }

  ll ea = (uit->second - lft + MOD) % MOD;
  ans = (ans + ea * val) % MOD;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    t[x]++;
  }
  dfs1(1);

  ll prev = 0;
  for (auto& [k, v] : c) {
    v = (v + prev) % MOD;
    prev = v;
  }

  dfs2(1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAXN] = lpow(fac[MAXN], MOD - 2, MOD);
  for (int i = MAXN - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
