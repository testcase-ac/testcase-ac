#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e4;

int sum_l(int n) {
  string n_str = to_string(n);
  ll pw = 1, len = 1, ret = 0;
  while (pw * 10 <= n) {
    ll add = 9 * pw * len % MOD;
    ret = (ret + add) % MOD;
    pw *= 10;
    ++len;
  }
  assert(pw <= n);
  ret = (ret + (n - pw + 1) * len) % MOD;
  return ret;
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
  int N, ans = 0; cin >> N;

  // a 아래첨자
  ans = (ans + lpow(2, N - 1, MOD) * sum_l(N)) % MOD;

  // a 개수
  ans = (ans + lpow(2, N - 1, MOD) * N) % MOD;

  // x 위첨자
  ans = (ans + sum_l(N) - 1 + MOD) % MOD;

  // x 개수
  ans = (ans + N) % MOD;

  // + 개수
  ans = (ans + lpow(2, N, MOD) - 1 + MOD) % MOD;

  // (, ) 개수
  ans = (ans + 2 * N - 2 + MOD) % MOD;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
