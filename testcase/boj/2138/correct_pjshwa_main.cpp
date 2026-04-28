#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int n; string s, t;
  cin >> n >> s >> t;

  int a[n], b[n];
  int ans = INF, cur;
  
  cur = 0;
  for (int i = 0; i < n; i++) a[i] = s[i] - '0', b[i] = t[i] - '0';
  for (int i = 1; i < n; i++) {
    if (a[i - 1] == b[i - 1]) continue;

    cur++;
    a[i - 1] ^= 1;
    a[i] ^= 1;
    if (i < n - 1) a[i + 1] ^= 1;
  }
  if (a[n - 1] == b[n - 1]) ans = min(ans, cur);

  cur = 1;
  for (int i = 0; i < n; i++) a[i] = s[i] - '0', b[i] = t[i] - '0';
  a[0] ^= 1, a[1] ^= 1;
  for (int i = 1; i < n; i++) {
    if (a[i - 1] == b[i - 1]) continue;

    cur++;
    a[i - 1] ^= 1;
    a[i] ^= 1;
    if (i < n - 1) a[i + 1] ^= 1;
  }
  if (a[n - 1] == b[n - 1]) ans = min(ans, cur);

  if (ans == INF) cout << "-1\n";
  else cout << ans << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
