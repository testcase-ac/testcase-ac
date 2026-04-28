#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// area of triangle
double area_tri(double x1, double y1, double x2, double y2, double x3, double y3) {
  return abs((x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2) / 2);
}

void solve() {
  int N; cin >> N;
  vector<pii> A(N);
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    A[i] = {x, y};
  }

  double ans = 0;
  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) for (int k = j + 1; k < N; k++) {
    auto [xi, yi] = A[i]; auto [xj, yj] = A[j]; auto [xk, yk] = A[k];
    ans = max(ans, area_tri(xi, yi, xj, yj, xk, yk));
  }
  cout << fixed << setprecision(1) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
