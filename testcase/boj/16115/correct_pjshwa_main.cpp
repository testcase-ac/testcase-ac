#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<pll> P(N); ll mdist = 0;
  for (int i = 0; i < N; i++) {
    ll x, y; cin >> x >> y;
    P[i] = {x, y}; mdist = max(mdist, x * x + y * y);
  }

  set<double> S;
  for (int i = 0; i < N; i++) {
    auto [x, y] = P[i];
    if (x * x + y * y != mdist) continue;

    // angle in degrees
    double angle = atan2(y, x) * 180 / M_PI;
    if (angle < 0) angle += 360;
    S.insert(angle);
  }
  vector<double> A(S.begin(), S.end());

  double mdiff = 0; int z = A.size();
  for (int i = 0; i < z; i++) {
    double u = A[i], v = A[(i + 1) % z];
    if (v <= u) v += 360;
    mdiff = max(mdiff, v - u);
  }
  cout << fixed << setprecision(10) << mdiff << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
