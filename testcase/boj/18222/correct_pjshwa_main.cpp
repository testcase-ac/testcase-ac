#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll k, pw = 1;
  cin >> k;
  k--;
  while (pw * 2 <= k) pw *= 2;

  int f = 0;
  while (1) {
    if (k == 0) {
      cout << f << '\n';
      break;
    }

    k -= pw;
    f ^= 1;
    while (pw > k) pw /= 2;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
