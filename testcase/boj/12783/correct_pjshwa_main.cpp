#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, INF = 1e9 + 7;
int d[MAX + 1], mask;

int r(int n) {
  if (d[n] != -1) return d[n];

  int cmask = 0, dn = n;
  while (dn) {
    cmask |= 1 << (dn % 10);
    dn /= 10;
  }
  if ((mask & cmask) == cmask) return d[n] = 0;

  int res = INF;
  for (int i = 2; i * i <= n; i++) {
    if (n % i) continue;
    int ra = r(n / i), rb = r(i);
    if (ra == INF || rb == INF) continue;
    res = min(res, ra + rb + 1);
  }

  return d[n] = res;
}

void solve() {
  int N;
  cin >> N;
  mask = 0;
  for (int i = 0, x; i < N; i++) {
    cin >> x;
    mask |= (1 << x);
  }
  memset(d, -1, sizeof(d));

  int Q;
  cin >> Q;
  while (Q--) {
    int n;
    cin >> n;

    int res = r(n);
    if (res == INF) cout << "-1\n";
    else cout << res << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
