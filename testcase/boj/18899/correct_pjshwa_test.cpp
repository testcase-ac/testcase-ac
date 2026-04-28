#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int n = s.size();

  ll ans = 0;
  for (int state = 1; state < (1 << n); state++) {
    string cur = "";
    for (int i = 0; i < n; i++) {
      if (state & (1 << i)) cur += s[i];
    }
    // cout << "state: " << state << " cur: " << cur << '\n';
    ans += stoll(cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
