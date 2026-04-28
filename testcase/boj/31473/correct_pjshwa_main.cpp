#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1000, MAXL = 1e6, INF = 1e18;
int A[MAXN], B[MAXN];

void solve() {
  int N; cin >> N;

  int asum = 0, bsum = 0;
  for (int i = 0; i < N; ++i) cin >> A[i], asum += A[i];
  for (int i = 0; i < N; ++i) cin >> B[i], bsum += B[i];

  ll ans = INF;
  for (ll a = 1; a <= MAXL; ++a) {
    ll bq = a * asum / bsum;
    for (ll b = bq - 3; b <= bq + 3; ++b) {
      if (b == 0) continue;
      ans = min(ans, abs(a * asum - b * bsum));
    }
  }

  // Find candidate
  for (ll a = 1; a <= MAXL; ++a) {
    ll bq = a * asum / bsum;
    for (ll b = bq - 3; b <= bq + 3; ++b) {
      if (b == 0) continue;

      ll cur = abs(a * asum - b * bsum);
      if (ans == cur) return cout << a << ' ' << b << '\n', void();
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
