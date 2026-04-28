#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[7];

void solve() {
  int k, os = 0;
  cin >> k;
  for (int i = 0; i < 7; i++) cin >> a[i], os += a[i];

  int ans = 1e9;
  for (int i = 0; i < 7; i++) {
    rotate(a, a + 1, a + 7);
 
    int cur, rem = k % os, s = os;
    if (rem) {
      int i = 0;
      while (rem) rem -= a[i++];
      cur = (k / s) * 7 + i;
    }
    else {
      cur = (k / s - 1) * 7;
      int i = 0;
      while (s) s -= a[i++];
      cur += i;
    }
    ans = min(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
