#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int a[MAX + 1], d[MAX + 1], p[MAX + 1][MAX + 10];
int n, k;

int r(int i) {
  if (i > n) return 0;
  if (d[i] != -1) return d[i];

  int ret = 0;
  for (int l = k;; l++) {
    if (p[i][l] == INF) break;
    ret = max(ret, r(p[i][l] + 1) + l);
  }
  return d[i] = ret;
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  for (int i = 1; i <= n; i++) {
    fill(p[i], p[i] + MAX + 10, INF);

    memset(d, 0, sizeof(d));
    for (int j = i; j <= n; j++) {
      d[j] = 1;
      for (int k = i; k < j; k++) {
        if (a[k] < a[j]) d[j] = max(d[j], d[k] + 1);
      }
      p[i][d[j]] = min(p[i][d[j]], j);
    }
  }

  for (k = 1; k <= n; k++) {
    memset(d, -1, sizeof(d));
    cout << r(1) << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
