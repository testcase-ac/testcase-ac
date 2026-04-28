#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200, INF = 1e9 + 7;
int a[MAX + 1], n;
int d[MAX + 1][MAX + 1];

int rec(int l, int r) {
  if (d[l][r] != -1) return d[l][r];
  if (l == r) return d[l][r] = 0;

  int res = INF;
  for (int i = l; i < r; i++) {
    res = min(res, rec(l, i) + rec(i + 1, r) + (a[l] != a[i + 1]));
  }
  return d[l][r] = res;
}

void solve() {
  int k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> a[i];

  memset(d, -1, sizeof d);
  cout << rec(1, n) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
