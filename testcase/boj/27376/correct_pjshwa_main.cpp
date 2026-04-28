#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  vector<tuple<ll, ll, ll>> A;
  for (int i = 0; i < K; ++i) {
    int x, t, s; cin >> x >> t >> s;
    A.emplace_back(x, t, s);
  }
  sort(A.begin(), A.end());

  ll tot = 0, lx = 0;
  for (auto& [x, t, s] : A) {
    tot += x - lx; lx = x;
    ll r = (tot + 2 * t - s) % (2 * t);
    if (r >= t) tot += 2 * t - r;
  }
  tot += N - lx;
  cout << tot << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
