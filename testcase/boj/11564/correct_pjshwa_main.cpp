#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll k, a, b;
  cin >> k >> a >> b;

  if (a <= 0 && b >= 0) return cout << b / k + (-a) / k + 1 << '\n', void();
  if (a < 0) {
    swap(a, b);
    a = -a, b = -b;
  }
  cout << b / k - (a - 1) / k << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
