#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX], b[MAX];

void solve() {
  int n, k;
  cin >> n >> k;

  ll sum = 0;
  for (int i = 0; i < n; i++) cin >> a[i], a[i] %= k, sum += a[i];
  if (sum % k) return cout << "blobsad\n", void();

  sum = 0;
  int bi = 0;

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    if (sum + a[i] >= k) {
      b[bi] = k - sum;
      a[i] -= b[bi];

      ll lcum = 0, lsum = 0, rcum = 0, rsum = 0;
      for (int i = 0; i < bi; i++) {
        lsum += b[i];
        lcum += lsum;
      }

      ll cur = lcum;
      for (int i = bi - 1; i >= 0; i--) {
        lcum -= lsum;
        lsum -= b[i];
        rsum += b[i + 1];
        rcum += rsum;
        cur = min(cur, lcum + rcum);
      }

      ans += cur;
      sum = b[0] = a[i];
      a[i] = bi = 0;
    }
    else b[bi] = a[i], sum += a[i], a[i] = 0;
    bi++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
