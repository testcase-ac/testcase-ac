#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, x;
  cin >> n >> x;

  ll rem = x - 1000 * n;
  ll cur = 0;
  priority_queue<int> pq;
  for (int i = 0; i < n; i++) {
    int ai, bi;
    cin >> ai >> bi;
    cur += bi;
    pq.push(ai - bi);
  }

  ll ans = cur;
  while (rem >= 4000) {
    if (pq.empty() || pq.top() <= 0) break;

    rem -= 4000;
    cur += pq.top();
    ans = max(ans, cur);
    pq.pop();
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
