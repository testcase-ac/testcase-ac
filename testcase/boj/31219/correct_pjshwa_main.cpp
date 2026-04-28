#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 10;
ll X[MAXV], Y[MAXV];

double dist(int i, int j) {
  return sqrt((X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]));
}

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> X[i] >> Y[i];

  int p[n]; iota(p, p + n, 0); double ans = 1e18;
  do {
    double cur = 0;
    for (int i = 0; i < n - 1; ++i) cur += dist(p[i], p[i + 1]);
    cur += dist(p[n - 1], p[0]);
    ans = min(ans, cur);
  } while (next_permutation(p, p + n));

  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
