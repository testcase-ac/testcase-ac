#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 4000, MOD = 1e9 + 7;
int C[MAXN + 1][MAXN + 1];

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
  int N; string S; cin >> N >> S;

  ll ans = 0;
  for (int i = 0; i < N; ++i) {
    int str = i;
    while (str < N && S[str] == '>') ++str;
    int len = str - i;
    if (len == 0 || str + len > N) continue;

    int ok = 1;
    for (int j = str; j < str + len; ++j) {
      if (S[j] == '>') ok = 0;
    }
    if (ok) ans = (ans + C[N - 2 * len][i]) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  C[0][0] = 1;
  for (int i = 1; i <= MAXN; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
