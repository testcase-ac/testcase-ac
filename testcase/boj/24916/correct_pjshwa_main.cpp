#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 25;
int a[MAX];
int d[MAX][MAX][2][2];
int n;

bool rec(int l, int r, bool c, bool p) {
  if (d[l][r][c][p] != -1) return d[l][r][c][p];

  bool res;
  if (l == 0 && r == n - 1) res = true;
  else {
    res = false;
    int pmove;
    if (l == r) pmove = 0;
    else if (c == 0 && p == 0) pmove = a[l + 1] - a[l];
    else if (c == 1 && p == 1) pmove = a[r] - a[r - 1];
    else pmove = a[r] - a[l];

    if (r < n - 1) {
      int nmove;
      if (c == 0) nmove = a[r + 1] - a[l];
      else nmove = a[r + 1] - a[r];
      if (nmove >= 2 * pmove) res |= rec(l, r + 1, 1, c);
    }
    if (l > 0) {
      int nmove;
      if (c == 0) nmove = a[l] - a[l - 1];
      else nmove = a[r] - a[l - 1];
      if (nmove >= 2 * pmove) res |= rec(l - 1, r, 0, c);
    }
  }

  return d[l][r][c][p] = res;
}

void solve() {
  cin >> n;
  if (n > MAX) {
    for (int i = 0, x; i < n; i++) cin >> x, cout << "NO\n";
    return;
  }
  for (int i = 0; i < n; i++) cin >> a[i];

  memset(d, -1, sizeof(d));
  for (int s = 0; s < n; s++) {
    if (rec(s, s, 1, 0) || rec(s, s, 0, 0)) cout << "YES\n";
    else cout << "NO\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
