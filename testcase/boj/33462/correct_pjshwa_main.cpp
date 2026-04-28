#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, D, X; cin >> n >> D >> X;

  vector<pii> V(n);
  for (int i = 0; i < n; ++i) cin >> V[i].first;
  for (int i = 0; i < n; ++i) cin >> V[i].second;
  sort(V.begin(), V.end());
  V.push_back({X, 0});

  int ans = 0;
  priority_queue<int> pq;
  for (auto& [x, g] : V) {
    while (x > D) {
      if (pq.empty()) return cout << "-1\n", void();
      D += pq.top(); pq.pop();
      ++ans;
    }
    pq.push(g);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
