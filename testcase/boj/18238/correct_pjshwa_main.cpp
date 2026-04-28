#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int dist(char a, char b) {
  return min(abs(a - b), 26 - abs(a - b));
}

void solve() {
  string s;
  cin >> s;

  int ans = dist('A', s[0]);
  for (int i = 0; i < s.size() - 1; i++) {
    ans += dist(s[i], s[i + 1]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
