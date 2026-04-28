#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int dt[MAX + 1], dv[MAX + 1];

void solve() {
  string s;
  cin >> s;

  int n = s.size();
  for (int i = 1; i <= n; i++) {
    if (s[i - 1] == '(') dt[i] = dt[i - 1] + 1;
    else dt[i] = dt[i - 1] - 1;
  }
  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == ')') dv[i] = dv[i + 1] + 1;
    else dv[i] = dv[i + 1] - 1;
  }

  int ans = 0;
  if (dt[n] == 1) {
    for (int i = n; i >= 1; i--) {
      if (dt[i] == 0) break;
      if (s[i - 1] == '(') ans++;
    }
  }
  else {
    for (int i = 0; i < n; i++) {
      if (dv[i] == 0) break;
      if (s[i] == ')') ans++;
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
