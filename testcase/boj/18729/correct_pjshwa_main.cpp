#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k; cin >> n >> k;

  priority_queue<ll> pq;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    pq.push(x);
  }

  ll ans1 = 0, ans2 = 0;
  while (k--) {
    ans1 = max(ans1, pq.top());
    pq.pop();
  }
  while (!pq.empty()) {
    ans2 += pq.top();
    pq.pop();
  }
  cout << max(ans1, ans2) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
