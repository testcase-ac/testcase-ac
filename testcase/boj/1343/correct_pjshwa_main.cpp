#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int n = s.size();

  int streak = 0;
  string ans = "";
  for (int i = 0; i < n; i++) {
    if (s[i] == 'X') streak++;
    else {
      while (streak >= 4) ans += "AAAA", streak -= 4;
      while (streak >= 2) ans += "BB", streak -= 2;
      if (streak) return cout << "-1\n", void();
      ans += '.';
    }
  }

  while (streak >= 4) ans += "AAAA", streak -= 4;
  while (streak >= 2) ans += "BB", streak -= 2;
  if (streak) return cout << "-1\n", void();

  cout << ans << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
