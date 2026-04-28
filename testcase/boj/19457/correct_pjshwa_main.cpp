#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int a[MAX + 10], N;

// minimum rope length to get from i-th ledge to the ground
ld rec(int i) {
  if (i == N + 1) return 0.0l;

  ld nxt = rec(i + 1);
  ld hgt = a[i] - a[i + 1];
  ld need = max(hgt - nxt / 2, 0.0l);
  return nxt + need;
}

void solve() {
  cin >> N >> a[0];
  for (int i = 1; i <= N; ++i) cin >> a[i];
  cout << fixed << setprecision(10) << rec(0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
