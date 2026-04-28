#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 16;
int B[MAX], n;
double P[MAX], d[1 << MAX][MAX + 1];

double r(int s, int l, int rem) {
  if (d[s][l] != -1) return d[s][l];
  if (l == 0) return d[s][l] = 1;

  double ret = 0;
  for (int i = 0; i < n; i++) {
    if (s & (1 << i)) continue;
    if (rem < B[i]) continue;

    ret = max(
      ret,
      r(s | (1 << i), l, rem - B[i]) * (1 - P[i]) + r(s | (1 << i), l - 1, rem - B[i]) * P[i]
    );
  }
  return d[s][l] = ret;
}

void solve() {
  int c, m; cin >> n >> c >> m;
  for (int i = 0; i < n; i++) cin >> B[i] >> P[i], P[i] /= 100;

  for (int i = 0; i < (1 << n); i++) for (int j = 0; j <= c; j++) d[i][j] = -1;
  cout << fixed << setprecision(10) << r(0, c, m) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
