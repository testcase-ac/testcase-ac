#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string S, T;
  cin >> S >> T;
  int sz = S.size(), tz = T.size();
  int diff = sz - tz, u = diff / 2;

  bool awin;
  if (sz == tz) {
    awin = S == T;
  }
  else if (diff & 1) {
    awin = S.substr(u, tz) == T;
    awin &= (S.substr(u + 1, tz) == T);
  }
  else {
    awin = S.substr(u, tz) == T;
    awin |= (S.substr(u + 1, tz) == T && S.substr(u - 1, tz) == T);
  }

  if (awin) cout << "Alice\n";
  else cout << "Bob\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
