#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S, T; cin >> S >> T;

  int sz = S.size(), tz = T.size(), ans = tz;
  for (int i = 0; i < tz - sz + 1; i++) {
    int dif = 0;
    for (int j = 0; j < sz; j++) dif += S[j] != T[i + j];
    ans = min(ans, dif);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
