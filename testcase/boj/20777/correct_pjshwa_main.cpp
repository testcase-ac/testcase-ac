#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n, x, t;
  cin >> n >> x >> t;
  
  ll lwait = max(0LL, x - 2 * (n - 1) * t), rwait = max(0LL, x - 2 * n * t);
  cout << min(4 * n * t + lwait, (4 * n + 1) * t + rwait) << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
