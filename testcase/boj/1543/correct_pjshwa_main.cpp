#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S, T; getline(cin, S); getline(cin, T);

  int sz = S.size(), tz = T.size(), ans = 0, i = 0;
  while (i < sz - tz + 1) {
    bool eq = true;
    for (int j = 0; j < tz; j++) eq &= S[i + j] == T[j];

    if (eq) ans++, i += tz;
    else i++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
