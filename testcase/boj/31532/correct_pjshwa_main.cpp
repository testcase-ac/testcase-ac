#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, b; cin >> N >> b;
  vector<pair<ll, ll>> pts;
  for (int i = 0; i < N; ++i) {
    ll x, y; cin >> x >> y;
    pts.emplace_back(x, y - b);
  }
  sort(pts.begin(), pts.end(), [](auto &a, auto &b) {
    return a.first * b.second > a.second * b.first;
  });

  // for (int i = 0; i < N; ++i) {
  //   auto [x, y] = pts[i];
  //   double a = (double)y / x, sum = 0;
  //   for (auto& [xx, yy] : pts) {
  //     sum += pow(yy - a * xx, 3);
  //   }
  //   cout << "i = " << i << ", a = " << a << ", sum = " << sum << '\n';
  // }

  ld l = -2e6, r = 2e6;
  for (int t = 0; t < 400; ++t) {
    ld a = (l + r) / 2, sum = 0;
    for (auto& [x, y] : pts) sum += pow(y - a * x, 3);
    if (sum < 0) r = a;
    else l = a;
  }
  cout << fixed << setprecision(10) << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
