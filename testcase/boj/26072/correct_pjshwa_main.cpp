#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, L;
  cin >> N >> L;
  vector<int> x(N), w(N);
  for (int i = 0; i < N; ++i) cin >> x[i];
  for (int i = 0; i < N; ++i) cin >> w[i];

  ld left = 0, right = L;
  for (int i = 0; i < 100; ++i) {
    ld mid = (left + right) / 2;
    ld lsum = 0, rsum = 0;
    for (int j = 0; j < N; ++j) {
      if (x[j] < mid) lsum += w[j] * (mid - x[j]);
      else rsum += w[j] * (x[j] - mid);
    }

    if (lsum < rsum) left = mid;
    else right = mid;
  }

  cout << fixed << setprecision(10) << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
