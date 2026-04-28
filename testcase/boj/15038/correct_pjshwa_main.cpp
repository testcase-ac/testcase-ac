#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Tx, Ty, N; cin >> Tx >> Ty >> N;

  map<pii, vector<pair<ll, int>>> M;
  for (int i = 0; i < N; ++i) {
    int x, y, h; cin >> x >> y >> h;
    ll dx = x - Tx, dy = y - Ty;
    ll g = abs(__gcd(dx, dy));
    M[{dx / g, dy / g}].push_back({dx * dx + dy * dy, h});
  }

  int ans = 0;
  for (auto& [_, v] : M) {
    sort(v.begin(), v.end());

    // take LIS of vector
    vector<int> L;
    for (auto& [_, h] : v) {
      if (L.empty() || h > L.back()) L.push_back(h);
      else *lower_bound(L.begin(), L.end(), h) = h;
    }
    ans += L.size();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
