#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
} 

const int INF = 1e9 + 5;

void solve() {
  set<pll> S; ll ans = 0;
  S.insert({0, INF}); S.insert({INF, 0});

  int Q; cin >> Q;
  while (Q--) {
    ll x, y; cin >> x >> y;

    auto it = S.lower_bound({x, y});
    if (it->second >= y) {
      cout << ans << '\n';
      continue;
    }

    auto [cx, cy] = *it;
    while (1) {
      auto p1 = prev(it);
      if (p1->second <= y) {
        auto p2 = prev(p1);
        ans -= (p1->first - p2->first) * (p1->second - cy);
        S.erase(p1);
      }
      else {
        ans += (x - p1->first) * (y - cy);
        break;
      }
    }

    S.insert({x, y});
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
