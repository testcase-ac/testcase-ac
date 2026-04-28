#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int m;
  cin >> m;

  int ans = m;
  while (m--) {
    string s;
    cin >> s;
    if (s.size() > 4) ans--;
    else if (s.size() == 4) {
      if (s[2] == '9' && s[3] != '0') ans--;
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
