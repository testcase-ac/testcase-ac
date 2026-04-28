#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;
  vector<pll> P(N);
  for (int i = 0; i < N; i++) {
    ll x, y;
    cin >> x >> y;
    P[i] = {x, y};
  }

  ll sx, sy;
  cin >> sx >> sy;

  bool f;
  
  // Goes north
  f = true;
  for (int i = 0; i < N; i++) {
    auto [x, y] = P[i];
    if (sx - abs(y - sy) >= x) {
      f = false;
      break;
    }
  }
  if (f) return cout << "YES\n", void();

  // Goes south
  f = true;
  for (int i = 0; i < N; i++) {
    auto [x, y] = P[i];
    if (sx + abs(y - sy) <= x) {
      f = false;
      break;
    }
  }
  if (f) return cout << "YES\n", void();

  // Goes west
  f = true;
  for (int i = 0; i < N; i++) {
    auto [x, y] = P[i];
    if (sy - abs(x - sx) >= y) {
      f = false;
      break;
    }
  }
  if (f) return cout << "YES\n", void();

  // Goes east
  f = true;
  for (int i = 0; i < N; i++) {
    auto [x, y] = P[i];
    if (sy + abs(x - sx) <= y) {
      f = false;
      break;
    }
  }
  if (f) return cout << "YES\n", void();

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
