#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ld EPS = 1e-9;
vector<ld> a;
int n;

ld eval(ld x) {
  int pw = 2 * n; ld ret = 0;
  for (int i = 0; i <= n; ++i) {
    ld term = a[i];
    for (int j = 0; j < pw; ++j) term *= x;
    ret += term;

    pw -= 2;
  }
  return ret;
}

void solve() {
  cin >> n;
  a.resize(n + 1);
  for (int i = 0; i <= n; ++i) cin >> a[i];

  double root;
  for (int r = 0; r <= 32; r++) {
    if (eval(r) == 0) {
      root = r;
      break;
    }

    bool r1 = eval(r) > 0, r2 = eval(r + 1) > 0;
    if (r1 ^ r2) {
      double lo = r, hi = r + 1;
      for (int i = 0; i < 100; ++i) {
        double mid = (lo + hi) / 2;
        if (r2 ^ (eval(mid) > 0)) lo = mid;
        else hi = mid;
      }
      root = lo;
      break;
    }
  }

  int k;
  cin >> k;
  k /= 2;

  ld w = root / k, s = 0, ans = 0;
  for (int i = 0; i < k; i++) {
    ld mid = (2 * s + w) / 2, fmid = eval(mid);
    ans += abs(fmid * w);
    s += w;
  }

  cout << fixed << setprecision(10) << 2 * ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
