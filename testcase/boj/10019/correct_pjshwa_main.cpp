#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
double A[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];

  double left = 1, right = 1e4;
  for (int i = 0; i < 100; i++) {
    double mid = (left + right) / 2;

    double tsum = 0;
    for (int i = 1; i <= N; i++) tsum += A[i] - mid;

    double rsum = -1e9, rcur = 0;
    for (int i = 2; i <= N - 1; i++) {
      rcur += A[i] - mid;
      if (rsum < rcur) rsum = rcur;
      if (rcur < 0) rcur = 0;
    }

    if (tsum > rsum) left = mid;
    else right = mid;
  }

  cout << fixed << setprecision(3) << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
