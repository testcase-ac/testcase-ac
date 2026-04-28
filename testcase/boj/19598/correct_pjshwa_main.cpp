#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
pii a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  sort(a, a + n);

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < n; i++) {
    auto [s, e] = a[i];
    if (pq.empty() || pq.top() > s) pq.push(e);
    else {
      pq.pop();
      pq.push(e);
    }
  }

  cout << pq.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
