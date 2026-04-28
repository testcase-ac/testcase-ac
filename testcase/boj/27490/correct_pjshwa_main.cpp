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

const int MAX = 3000, MOD = 1e9 + 7;
int a[MAX];

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  // Answer is # of balls moving right, with previous ball moving left
  ll ans = (lpow(2, n, MOD) - n - 1 + MOD) % MOD;
  for (int i = 2; i < n - 1; i++) {
    // Bounds of balls
    int l = i - 2, r = i + 1;

    // Iterate for each previous ball
    // This ball should move left, in other words, a[j] - a[l] <= a[i] - a[j]
    for (int j = i - 1; j >= 1; j--) {
      l = min(l, j - 1);
      while (l > 0 && a[j] - a[l - 1] <= a[i] - a[j]) l--;

      // Ball i should move right, in other words, a[r] - a[i] < a[i] - a[j]
      while (r < n - 1 && a[r + 1] - a[i] < a[i] - a[j]) r++;

      // Do not count if ball i is not moving right
      // OR ball j is not moving left
      if (a[r] - a[i] >= a[i] - a[j] || a[j] - a[l] > a[i] - a[j]) continue;

      // Balls from i + 1 to r, cannot all be not chosen
      // Balls from l to j - 1, cannot all be not chosen
      // Balls from 0 to l - 1 and r + 1 to n - 1 can be either chosen or not
      ll add = lpow(2, l + n - 1 - r, MOD);
      add = add * (lpow(2, r - i, MOD) - 1 + MOD) % MOD;
      add = add * (lpow(2, j - l, MOD) - 1 + MOD) % MOD;
      ans = (ans + add) % MOD;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
