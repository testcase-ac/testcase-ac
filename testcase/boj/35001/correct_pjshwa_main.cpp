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

const int MAXN = 20, MAXP = 3e5, MOD = 1e9 + 7;
int A[MAXN], P[MAXP + 1], dp[1 << MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> A[i];

  dp[0] = 1; int ans = 0;
  for (int s = 1; s < (1 << N); ++s) {
    int sum = 0, cnt = N;
    for (int i = 0; i < N; ++i) if (!(s & (1 << i))) sum += A[i] * A[i], --cnt;
    if (cnt > M) continue;

    for (int i = 0; i < N; ++i) if (s & (1 << i)) {
      ll c = A[i] * A[i];
      ll pre = dp[s ^ (1 << i)], prob = c * P[sum + c] % MOD;
      dp[s] = (dp[s] + pre * prob) % MOD;
    }
    if (cnt == M && (s & 1)) ans = (ans + dp[s]) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  for (int p = 1; p <= MAXP; ++p) P[p] = lpow(p, MOD - 2, MOD);

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
