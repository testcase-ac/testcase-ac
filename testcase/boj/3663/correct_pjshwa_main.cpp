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
  int n = s.size();

  int ans = 0, pos = 1e9;
  for (int i = 0; i < n; i++) ans += dist(s[i], 'A');

  int j;
  for (int i = 0; i < n; i++) {
    for (j = i + 1; j < n && s[j] == 'A'; j++);
    if (s[i] == 'A' && j == n + 1) break;
    pos = min({i * 2 + n - j, i + (n - j) * 2, pos});
  }

  cout << ans + pos << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
