#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int pow(int n, int k) {
  int ret = 1;
  for (int i = 0; i < k; i++) ret *= n;
  return ret;
}

int n, k;
char r(int s, int i, int j) {
  if (s == 0) return '0';

  int len = pow(n, s), seg = len / n;
  int u = (n - k) / 2;
  if (i < seg * u || j < seg * u || i >= seg * (n - u) || j >= seg * (n - u)) {
    return r(s - 1, i % seg, j % seg);
  }
  else return '1';
}

void solve() {
  int s, r1, r2, c1, c2;
  cin >> s >> n >> k >> r1 >> r2 >> c1 >> c2;
  for (int i = r1; i <= r2; i++) {
    for (int j = c1; j <= c2; j++) cout << r(s, i, j);
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
