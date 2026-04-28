#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXB = 18, MAXN = 4e5, MOD = 1e9 + 7;
int dp[MAXB + 1][MAXN + 1];

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
  int N, M, K; cin >> N >> M >> K;

  vector<int> S(M);
  for (int i = 0; i < M; ++i) cin >> S[i];
  reverse(S.begin(), S.end());

  bool has_one = S.back() == 1;
  if (has_one) S.pop_back();
  M = S.size();
  reverse(S.begin(), S.end());

  dp[0][1] = 1;
  for (int b = 0; b < MAXB; ++b) {
    for (int v = 1; v <= K; ++v) {
      for (int i = 0; i < M; ++i) {
        ll val = 1LL * v * S[i];
        if (val > K) break;
        dp[b + 1][val] = (dp[b + 1][val] + dp[b][v]) % MOD;
      }
    }
  }

  cout << has_one << ' ';
  for (int k = 2; k <= K; ++k) {
    if (has_one) {
      ll ans = 0, coef = 1;
      for (int b = 1; b <= MAXB; ++b) {
        coef = coef * lpow(b, MOD - 2, MOD) % MOD;
        coef = coef * (N - b + 1) % MOD;

        ll cur = dp[b][k] * coef % MOD;
        ans = (ans + cur) % MOD;
      }
      cout << ans << ' ';
    }
    else {
      if (N <= MAXB) cout << dp[N][k] << ' ';
      else cout << "0 ";
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
