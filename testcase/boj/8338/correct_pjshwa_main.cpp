#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e6;
string A[MAX];

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int m, n; string s;
  cin >> m >> n >> s;

  int C = 0, S = -1;
  for (int i = 0; i < m; i++) {
    if (s[i] == '0') {
      if (S == -1) S = 0;
      if (S == 1) C++, S = -1;
    }
    if (s[i] == '1') {
      if (S == -1) S = 1;
      if (S == 0) C++, S = -1;
    }
  }

  if (C >= n) cout << "0\n";
  else {
    int ans = 2 * (n - C);
    if (S > -1) ans--;
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
