#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll C2(ll n) {
  return n * (n - 1) / 2;
}

void solve() {
  int N; cin >> N;
  vector<pair<ll, ll>> A;
  for (int i = 0; i < N; ++i) {
    ll a, b; cin >> a >> b;
    A.emplace_back(a, b);
  }

  ll ans = 0;
  for (auto& [x, y] : A) {
    unordered_map<ll, int> d_tal;
    set<pair<ll, ll>> sym_pts_set;
    for (auto& [a, b] : A) {
      if (a == x && b == y) continue;
      sym_pts_set.emplace(a, b);
      ll dist = (a - x) * (a - x) + (b - y) * (b - y);
      ++d_tal[dist];
    }
    for (auto& [_, cnt] : d_tal) ans += C2(cnt);

    int sym_cnt = 0;
    for (auto& [a, b] : A) {
      if (a == x && b == y) continue;
      ll sym_a = x + (x - a), sym_b = y + (y - b);
      if (sym_pts_set.count({sym_a, sym_b})) ++sym_cnt;
    }
    ans -= sym_cnt / 2;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
