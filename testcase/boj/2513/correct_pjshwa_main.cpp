#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int p[MAX + 1];

void solve() {
  int n, k, s;
  cin >> n >> k >> s;

  priority_queue<pii> px;
  priority_queue<pii, vector<pii>, greater<pii>> pm;
  for (int i = 0; i < n; i++) {
    int x, u;
    cin >> x >> u;
    px.push({x, u});
    pm.push({x, u});
  }

  int cur, sta, ans = 0;

  cur = 0;
  while (!px.empty()) {
    auto [x, u] = px.top();
    px.pop();

    if (x < s) break;

    if (cur == 0) sta = x;
    cur += u;

    if (cur >= k) {
      if (cur > k) px.push({x, cur - k});
      ans += (sta - s);
      cur = 0;
    }
  }

  if (cur > 0) ans += (sta - s);

  cur = 0;
  while (!pm.empty()) {
    auto [x, u] = pm.top();
    pm.pop();

    if (x > s) break;

    if (cur == 0) sta = x;
    cur += u;

    if (cur >= k) {
      if (cur > k) pm.push({x, cur - k});
      ans += (s - sta);
      cur = 0;
    }
  }

  if (cur > 0) ans += (s - sta);

  cout << ans * 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
