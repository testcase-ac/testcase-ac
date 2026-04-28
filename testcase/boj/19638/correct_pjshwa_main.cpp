#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, h, t, x;
  cin >> n >> h >> t;

  priority_queue<int> pq;
  for (int i = 0; i < n; i++) {
    cin >> x;
    pq.push(x);
  }

  if (pq.top() < h) return cout << "YES\n0\n", void();

  for (int i = 1; i <= t; i++) {
    int x = pq.top();
    if (x == 1) break;
    pq.pop();
    pq.push(x / 2);
    if (pq.top() < h) return cout << "YES\n" << i << '\n', void();
  }

  cout << "NO\n" << pq.top() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
