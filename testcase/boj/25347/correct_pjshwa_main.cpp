#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int R[MAXN], B[MAXN];

void solve() {
  int n, x, y; cin >> n >> x >> y;

  ll rsum = 0, bsum = 0;
  for (int i = 0; i < n; ++i) cin >> R[i], rsum += R[i];
  for (int i = 0; i < n; ++i) cin >> B[i], bsum += B[i];

  for (int i = 0; i < n; ++i) {
    ld rp = (ld)R[i] / rsum;
    ld bp = (ld)B[i] / bsum;

    cout << "rp = " << rp << ", bp = " << bp << '\n';

    ld pi_max = (rp + bp) * x / (bp * y);
    cout << fixed << setprecision(10) << pi_max << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
