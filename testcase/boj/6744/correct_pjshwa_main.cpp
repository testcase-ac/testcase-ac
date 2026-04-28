#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int nC2(int n) {
  return n * (n - 1) / 2;
}

// x, y can be upto 2e9
ll to_v(int x, int y) {
  return (ll)x * 4000000000LL + (ll)y;
}

void solve() {
  int N; cin >> N; vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
  }

  vector<ll> V;
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    auto [ax, ay] = A[i]; auto [bx, by] = A[j];
    V.emplace_back(to_v(ax + bx, ay + by));
  }
  sort(V.begin(), V.end());

  ll ans = 0, Z = V.size(), str = 1;
  for (int i = 1; i < Z; ++i) {
    if (V[i] == V[i - 1]) ++str;
    else {
      ans += nC2(str);
      str = 1;
    }
  }
  ans += nC2(str);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
