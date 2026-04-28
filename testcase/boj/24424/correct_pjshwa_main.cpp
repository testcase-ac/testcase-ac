#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;

  ll ans = 0;
  priority_queue<pll> pq;
  pq.push({0, 0});

  for (int i = 0; i < n; i++) {
    int a, v;
    cin >> a >> v;

    auto [tv, ta] = pq.top();
    if (ta == a) {
      pq.pop();
      while (pq.top().second == a) pq.pop();

      ll nv = pq.top().first + v;
      ans = max(ans, nv);
      pq.push({tv, ta});
      pq.push({nv, a});
    }
    else {
      ans = max(ans, tv + v);
      pq.push({tv + v, a});
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
