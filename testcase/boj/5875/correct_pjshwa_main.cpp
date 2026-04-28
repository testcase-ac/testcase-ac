#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int n = s.size(), l = 0, r = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') l++;
    else r++;
  }

  int run = 0, ans = 0;
  if (l < r) {
    for (int i = 0; i < n; i++) {
      if (s[i] == '(') run++;
      else run--, ans++;

      if (run < 0) break;
    }
  }
  else if (l > r) {
    for (int i = n - 1; i >= 0; i--) {
      if (s[i] == '(') run--, ans++;
      else run++;

      if (run < 0) break;
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
