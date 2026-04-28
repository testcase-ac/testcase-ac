#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int n;
  cin >> n;

  deque<int> d;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    d.push_back(x);
  }

  int ans = 0, pre = 0;
  for (int i = 0; i < n; i++) {
    if (d.front() <= d.back()) {
      if (pre <= d.front()) ans++;
      pre = max(pre, d.front());
      d.pop_front();
    }
    else {
      if (pre <= d.back()) ans++;
      pre = max(pre, d.back());
      d.pop_back();
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
