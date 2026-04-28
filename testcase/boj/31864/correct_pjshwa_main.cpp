#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<pii, vector<ll>> D;

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    ll fx, fy; cin >> fx >> fy;
    ll d = fx * fx + fy * fy;

    ll g = abs(gcd(fx, fy));
    fx /= g, fy /= g;
    D[{fx, fy}].push_back(d);
  }

  for (auto& [_, v] : D) sort(v.begin(), v.end());

  int ans = 0;
  while (M--) {
    ll ex, ey; cin >> ex >> ey;
    ll d = ex * ex + ey * ey;

    ll g = abs(gcd(ex, ey));
    ex /= g, ey /= g;

    if (!D.count({ex, ey})) continue;
    auto& V = D[{ex, ey}];
    auto it = upper_bound(V.begin(), V.end(), d);
    ans = max(ans, (int)(it - V.begin()));
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
