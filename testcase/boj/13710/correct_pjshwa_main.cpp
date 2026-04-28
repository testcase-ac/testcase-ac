#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int v[MAX];

void solve() {
  int n;
  cin >> n;

  ll ans = 0;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    for (int b = 0; b < 30; b++) {
      if (x & (1 << b)) v[b] = (i - v[b]) + 1;
      ans += (ll)v[b] * (1 << b);
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
