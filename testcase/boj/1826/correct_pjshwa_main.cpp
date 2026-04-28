#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000;
pii stops[MAX + 1];

void solve() {
  int n, l, p;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> stops[i].first >> stops[i].second;
  cin >> l >> p;
  stops[n++] = {l, 0};
  sort(stops, stops + n);

  priority_queue<int> pq;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    auto [a, b] = stops[i];
    while (p < a) {
      if (pq.empty()) return cout << "-1\n", void();
      p += pq.top();
      pq.pop();
      ans++;
    }
    pq.push(b);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
