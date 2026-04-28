#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll sum_i1(ll n) {
  return n * (n + 1) / 2;
}

ll sum_i2(ll n) {
  return n * (n + 1) * (2 * n + 1) / 6;
}

void solve() {
  ll R, C;
  cin >> R >> C;

  ll N = min(R, C) - 1;
  ll w = 2 * (R * C * N - R * sum_i1(N) - C * sum_i1(N) + sum_i2(N)) + R * C;
  ll b = 2 * (R * C * N - R * sum_i1(N) - C * sum_i1(N) + sum_i2(N) + sum_i1(N)) - (R + C) * N + 2 * R * C - R - C;
  cout << w << ' ' << b << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
