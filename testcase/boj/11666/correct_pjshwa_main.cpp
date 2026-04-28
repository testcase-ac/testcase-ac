#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
pii a[MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  sort(a, a + n);

  int ans = 0;
  priority_queue<int, vector<int>, greater<int>> et;
  et.push(a[0].first + a[0].second);
  for (int i = 1; i < n; i++) {
    auto [s, t] = a[i];
    while (!et.empty() && s - et.top() > m) et.pop();
    if (!et.empty() && s >= et.top() && s - et.top() <= m) {
      ans++;
      et.pop();
    }
    et.push(s + t);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
