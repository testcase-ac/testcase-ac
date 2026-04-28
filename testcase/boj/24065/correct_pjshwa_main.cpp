#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, a;
  cin >> n >> a;
  
  ll ans = 0;
  for (int i = 1; i < n; i++) {
    if (i * i >= a) ans += (n - i) * (n - i);
    for (int j = 1; j < i; j++) {
      if (j * j + (i - j) * (i - j) >= a) ans += (n - i) * (n - i);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
