#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m; cin >> n >> m;

  priority_queue<ll, vector<ll>, greater<ll>> pq;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    pq.push(x);
  }

  while (m--) {
    ll x1 = pq.top(); pq.pop();
    ll x2 = pq.top(); pq.pop();

    pq.push(x1 + x2);
    pq.push(x1 + x2);
  }

  ll ans = 0;
  while (!pq.empty()) ans += pq.top(), pq.pop();
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
