#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  priority_queue<ll, vector<ll>, greater<ll>> pq;

  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    ll x; cin >> x;
    if (x) pq.push(x), ans = max(ans, x);
  }

  while (pq.size() >= 2) {
    ll t1 = pq.top(); pq.pop();
    ll t2 = pq.top(); pq.pop();
    ans = max(ans, t1); ans = max(ans, t2);

    if (t1 == t2) pq.push(t1 + t2);
    else pq.push(t2);
  }
  if (pq.size()) ans = max(ans, pq.top());
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
