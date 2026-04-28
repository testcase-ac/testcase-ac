#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  int ans = (n / 18) * 2;
  n %= 18;

  if (n > 0) {
    if (n < 10) ans += 1;
    else if (n & 1) ans += 3;
    else ans += 2;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
