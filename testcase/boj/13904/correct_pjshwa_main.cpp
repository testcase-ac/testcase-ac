#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  vector<pii> wait;
  for (int i = 0, x, y; i < n; i++) {
    cin >> x >> y;
    wait.push_back({-x, y});
  }
  sort(wait.begin(), wait.end());

  int ans = 0, wi = 0;
  priority_queue<int> pq;
  for (int d = 1000; d >= 1; d--) {
    while (wi < n && -wait[wi].first >= d) {
      pq.push(wait[wi].second);
      wi++;
    }
    if (!pq.empty()) {
      ans += pq.top();
      pq.pop();
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
