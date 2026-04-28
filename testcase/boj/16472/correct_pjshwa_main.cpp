#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int m;
  string s;
  cin >> m >> s;
  int n = s.size();

  int ep = 0, uc = 0, ans = 0;
  map<int, int> u;
  for (int sp = 0; sp < n; sp++) {
    while (ep < n && uc <= m) {
      u[s[ep]]++;
      if (u[s[ep]] == 1) uc++;
      ep++;
    }

    if (ep == n && uc <= m) ans = max(ans, ep - sp);
    ans = max(ans, ep - sp - 1);

    u[s[sp]]--;
    if (u[s[sp]] == 0) uc--;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
