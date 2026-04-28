#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, d;
  cin >> n >> d;

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    string s = to_string(i);
    for (char c : s) {
      if (c - '0' == d) ans++;
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
