#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
int d[3 * MAX + 1][3 * MAX + 1][3];

int n; string s;
int rec(int l, int r, int state) {
  if (d[l][r][state] != -1) return d[l][r][state];
  if (l == r) return 0;

  int res = 0;
  if (state == 0) {
    if (s[l] == 'B') res = max(res, rec(l + 1, r, 1) + 1);
    if (s[r - 1] == 'B') res = max(res, rec(l, r - 1, 1) + 1);
  }
  if (state == 1) {
    if (s[l] == 'L') res = max(res, rec(l + 1, r, 2) + 1);
    if (s[r - 1] == 'L') res = max(res, rec(l, r - 1, 2) + 1);
  }
  if (state == 2) {
    if (s[l] == 'D') res = max(res, rec(l + 1, r, 0) + 1);
    if (s[r - 1] == 'D') res = max(res, rec(l, r - 1, 0) + 1);
  }

  return d[l][r][state] = res;
}

void solve() {
  cin >> n >> s;

  memset(d, -1, sizeof(d));
  cout << rec(0, 3 * n, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
