#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  priority_queue<ll, vector<ll>, greater<ll>> pq;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    pq.push(x);
  }

  ll ans = 0;
  while (pq.size() >= 2) {
    ll a = pq.top(); pq.pop();
    ll b = pq.top(); pq.pop();
    ans += a + b; pq.push(a + b);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
