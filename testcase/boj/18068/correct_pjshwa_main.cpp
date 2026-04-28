#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, start = -710 * 25000;
  cin >> n;
  while (n--) cout << start << '\n', start += 710;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
