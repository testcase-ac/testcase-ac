#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int n;
  string s;
  cin >> n >> s;

  int ans = INF, cnt;
  bool flag;

  cnt = 0, flag = 0;
  for (int i = 0; i < n; i++) {
    if (!flag && s[i] == 'R') {
      cnt++;
      flag = 1;
    }
    if (flag && s[i] == 'B') flag = 0;
  }
  ans = min(ans, cnt + 1);

  cnt = 0, flag = 0;
  for (int i = 0; i < n; i++) {
    if (!flag && s[i] == 'B') {
      cnt++;
      flag = 1;
    }
    if (flag && s[i] == 'R') flag = 0;
  }
  ans = min(ans, cnt + 1);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
