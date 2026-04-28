#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
int a[MAXN], b[MAXN];

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];

  ll ans = 0;
  for (int l = 0; l < m; ++l) for (int r = 0; r < m && l + r < n; ++r) {
    int move = l + r + min(l, r);
    if (move > m) continue;

    int c = m - move;
    priority_queue<pii> pq;
    for (int oi = -l; oi <= r; ++oi) {
      int i = (oi + n) % n;
      pq.emplace(a[i], i);
    }

    ll cur = 0;
    while (c--) {
      auto [val, i] = pq.top(); pq.pop();
      cur += val;
      pq.emplace(max(0, val - b[i]), i);
    }
    ans = max(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
