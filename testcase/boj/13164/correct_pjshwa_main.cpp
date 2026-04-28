#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
int a[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll ans = 0;
  priority_queue<int> pq;
  for (int i = 0; i < n - 1; i++) {
    ans += (a[i + 1] - a[i]);
    pq.push(a[i + 1] - a[i]);
  }

  while (--k) {
    ans -= pq.top();
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
