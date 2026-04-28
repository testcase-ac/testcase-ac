#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll L, N, K; cin >> L >> N >> K;

  set<ll> vis; priority_queue<pll, vector<pll>, greater<pll>> pq;
  for (int i = 0; i < N; ++i) {
    ll x; cin >> x;
    vis.insert(x); pq.push({0, x});
  }

  while (K--) {
    auto [d, x] = pq.top(); pq.pop();
    cout << d << '\n';
    if (x > 0 && vis.count(x - 1) == 0) {
      vis.insert(x - 1);
      pq.push({d + 1, x - 1});
    }
    if (x < L && vis.count(x + 1) == 0) {
      vis.insert(x + 1);
      pq.push({d + 1, x + 1});
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
