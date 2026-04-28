#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll a[MAX], d[MAX];

void solve() {
  int h, n;
  cin >> h >> n;
  for (int i = 0; i < n; i++) cin >> a[i] >> d[i];

  ll ans = 0;
  for (int i = 0; i < n; i++) ans = max(ans, a[i]);

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  for (int i = 0; i < n; i++) pq.push({a[i] + d[i], i});

  while (h--) {
    pll p = pq.top(); pq.pop();
    ans = max(ans, p.first);
    pq.push({p.first + d[p.second], p.second});
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
