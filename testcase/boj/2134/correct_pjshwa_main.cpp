#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m, k; cin >> n >> m >> k;

  deque<pii> q;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    q.emplace_back(x, i);
  }

  ll cwgt = 0, csum = 0;
  for (int j = 1; j <= m; j++) {
    int y; cin >> y;

    while (y && !q.empty()) {
      auto [x, i] = q.front(); q.pop_front();

      cwgt += min(x, y);
      csum += min(x, y) * (i + j);

      if (x <= y) y -= x;
      else {
        q.emplace_front(x - y, i);
        y = 0;
      }
    }
  }
  cout << cwgt << ' ' << csum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
