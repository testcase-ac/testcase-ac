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

const int MAX = 100, MOD = 1e9 + 7;
ll fac[MAX * MAX + 1], ifac[MAX * MAX + 1];
char board[MAX + 1][MAX + 1];

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

void solve() {
  int n, k; cin >> n >> k;

  int rem = n * n;
  for (int i = 0; i < n; i++) {
    cin >> board[i];
    for (int j = 0; j < n; j++) rem -= board[i][j] == '1';
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    int def = n;
    for (int j = 0; j < n; j++) def -= board[i][j] == '1';
    ll val = C(rem - def, k - def) * fac[k] % MOD;
    ans = (ans + val) % MOD;
  }
  for (int j = 0; j < n; j++) {
    int def = n;
    for (int i = 0; i < n; i++) def -= board[i][j] == '1';
    ll val = C(rem - def, k - def) * fac[k] % MOD;
    ans = (ans + val) % MOD;
  }

  // 2 diagonals
  {
    int def = n;
    for (int i = 0; i < n; i++) def -= board[i][i] == '1';
    ll val = C(rem - def, k - def) * fac[k] % MOD;
    ans = (ans + val) % MOD;
  }
  {
    int def = n;
    for (int i = 0; i < n; i++) def -= board[i][n - i - 1] == '1';
    ll val = C(rem - def, k - def) * fac[k] % MOD;
    ans = (ans + val) % MOD;
  }

  for (int i = 0; i < k; i++) ans = (ans * lpow(rem - i, MOD - 2, MOD)) % MOD;
  ans = (ans * fac[n * n]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX * MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX * MAX] = lpow(fac[MAX * MAX], MOD - 2, MOD);
  for (int i = MAX * MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
