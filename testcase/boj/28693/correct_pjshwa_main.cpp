#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
 
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

const int MAXN = 1000, MOD = 1e9 + 7;

// Card pairs left, card pairs of which one is face up
ll dp[MAXN + 1][MAXN + 1];

ll r(int n, int k) {
  if (dp[n][k] != -1) return dp[n][k];
  if (n == k) return dp[n][k] = k;

  // First card flip
  // prob of flipping seen card = k / (2 * n - k)

  // if seen card is flipped, flip already face up card
  ll p1 = k * lpow(2 * n - k, MOD - 2, MOD) % MOD;
  ll v1 = ((k > 0 ? r(n - 1, k - 1) : 0) + 1) % MOD;
  ll a1 = (p1 * v1) % MOD;

  // if unseen card is flipped, we now consider this card as seen
  // there are now 3 cases:
  // 1. second flipped card is seen = k / (2 * n - k - 1)
  // 2. second flipped card is same as first flipped card = 1 / (2 * n - k - 1)
  // 3. second flipped card is unseen
  ll p1v = (1 - p1 + MOD) % MOD;

  // In 1st case we know one pair's location, so use another point to flip them
  ll p2 = k * lpow(2 * n - k - 1, MOD - 2, MOD) % MOD;
  ll v2 = (r(n - 1, k) + 2) % MOD;
  ll a2 = (p1v * p2) % MOD;
  a2 = (a2 * v2) % MOD;

  // In 2nd case we just need to use 1 point
  ll p3 = lpow(2 * n - k - 1, MOD - 2, MOD);
  ll v3 = (r(n - 1, k) + 1) % MOD;
  ll a3 = (p1v * p3) % MOD;
  a3 = (a3 * v3) % MOD;

  // In 3rd case, k is incremented by 2
  ll p4 = (1 - p2 + MOD - p3 + MOD) % MOD;
  ll v4 = ((p4 > 0 ? r(n, k + 2) : 0) + 1) % MOD;
  ll a4 = (p1v * p4) % MOD;
  a4 = (a4 * v4) % MOD;

  ll ret = 0;
  for (ll a : {a1, a2, a3, a4}) ret = (ret + a) % MOD;
  return dp[n][k] = ret;
}

void solve() {
  int N; cin >> N;

  memset(dp, -1, sizeof(dp));
  cout << r(N, 0) << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
