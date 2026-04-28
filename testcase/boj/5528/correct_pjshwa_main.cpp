#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
int d[2][MAX + 1][MAX + 1];
string s, t;
int n, m;

int rec(int l, int r, int c) {
  if (l == n && r == m) return 0;
  if (d[c][l][r] != -1) return d[c][l][r];

  int lr = 0, rr = 0;
  if (c == 0) {
    if (l < n && s[l] == 'I') lr = rec(l + 1, r, 1) + 1;
    if (r < m && t[r] == 'I') rr = rec(l, r + 1, 1) + 1;
  }
  else {
    if (l < n && s[l] == 'O') lr = rec(l + 1, r, 0) + 1;
    if (r < m && t[r] == 'O') rr = rec(l, r + 1, 0) + 1;
  }
  return d[c][l][r] = max(lr, rr);
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));
  cin >> n >> m >> s >> t;

  int ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    ans = max(ans, rec(i, j, 0));
  }

  if (ans > 0 && ans % 2 == 0) ans--;
  cout << ans << '\n';
}
