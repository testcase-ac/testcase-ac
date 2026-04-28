#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string s; cin >> s;

  int ans = 0, streak = 0;
  for (char c : s) {
    if (c == '0') streak++;
    else {
      ans += streak;
      streak = 0;
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
