#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;

  int ans = 1, add = 1;
  for (int i = 1; i <= 8; i++) add *= i;

  int u[9]{};
  for (int i = 0; i < 9; i++) {
    for (char c = 'a'; c < S[i]; c++) {
      if (u[c - 'a']) continue;
      ans += add;
    }
    u[S[i] - 'a'] = 1;
    if (i < 8) add /= (8 - i);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
