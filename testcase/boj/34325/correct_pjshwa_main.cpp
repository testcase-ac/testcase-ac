#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

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

const int MAXN = 1e6, MOD = 1e9 + 7;
ll A[MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;
  A[1] = 1; A[2] = 4; A[3] = 13; A[4] = 24;
  for (int i = 5; i <= N; ++i) {
    ll v = 2 * A[i - 1];
    v = (v - 2 * A[i - 3] % MOD + MOD) % MOD;
    v = (v + A[i - 4]) % MOD;
    A[i] = v;
  }

  ll ans = 0;
  for (int i = 1; i <= N; ++i) {
    ll c = A[N - i + 1] * lpow(K, i, MOD) % MOD;
    ans = (ans + c) % MOD;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
