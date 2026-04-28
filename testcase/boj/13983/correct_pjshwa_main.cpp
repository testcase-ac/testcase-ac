#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1 << 21;
double fac[MAXN + 1];

double f(int L, int R, int i) {
  int u = 1 << i;
  // double tot = C(L - 1, u - 1);
  // return C(L - R, u - 1) / tot;

  if (L - R - u + 1 < 0) return 0;
  double val = fac[L - R] + fac[L - u] - fac[L - R - u + 1] - fac[L - 1];
  return pow(2, val);
}

void solve() {
  int K, R; cin >> K >> R;
  int L = 1 << K;

  double ans = 0;
  for (int i = K; i >= 1; i--) {
    double p1 = f(L, R, i), p2 = f(L, R, i + 1);
    ans += (p1 - p2) * i;
  }
  cout << fixed << setprecision(5) << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = 0;
  for (int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] + log2(i);

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
