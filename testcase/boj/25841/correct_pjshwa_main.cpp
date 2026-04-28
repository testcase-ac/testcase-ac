#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int L, R; string T;
  cin >> L >> R >> T;

  int ans = 0;
  for (int i = L; i <= R; i++) {
    string s = to_string(i);
    for (char& c : s) {
      if (c == T[0]) ans++;
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
