#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
int T[MAXN], X[MAXN];

void solve() {
  int N, C; cin >> N >> C;
  for (int i = 0; i < N; ++i) cin >> T[i];
  for (int i = 0; i < N; ++i) cin >> X[i];

  ld l = 0, r = 1e6 + 1;
  for (int t = 0; t < 100; ++t) {
    ld mid = (l + r) / 2, sum = 0; int ok = 1;
    for (int i = 0; i < N; ++i) {
      sum = max(0.0L, sum + T[i] * (X[i] - mid));
      if (sum > C) {
        ok = 0;
        break;
      }
    }
    if (ok) r = mid;
    else l = mid;
  }
  cout << fixed << setprecision(10) << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
