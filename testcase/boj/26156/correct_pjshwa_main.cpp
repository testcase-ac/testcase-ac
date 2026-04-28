#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, MOD = 1e9 + 7;
int d[3][MAX + 1];

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
  int N; string S;
  cin >> N >> S;

  for (int i = N - 1; i >= 0; i--) {
    for (int j = 0; j < 3; j++) {
      d[j][i] = d[j][i + 1];
    }
    if (S[i] == 'O') d[2][i] = (d[2][i] + d[1][i + 1]) % MOD;
    if (S[i] == 'C') d[1][i] = (d[1][i] + d[0][i + 1]) % MOD;
    if (S[i] == 'K') d[0][i] = (d[0][i] + 1) % MOD;
  }

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] != 'R') continue;

    ll lhs = lpow(2, i, MOD);
    ll rhs = d[2][i + 1];
    ans = (ans + lhs * rhs) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
