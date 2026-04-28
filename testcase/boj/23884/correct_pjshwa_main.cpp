#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
int a[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  priority_queue<pii> pq;
  for (int i = 0; i < n; i++) cin >> a[i], pq.push({a[i], i});

  for (int i = n - 1; i > 0; i--) {
    while (pq.top().second > i) pq.pop();

    if (pq.top().second == i) continue;
    else {
      int j = pq.top().second;
      swap(a[i], a[j]);
      pq.pop();
      pq.push({a[j], j});
      if (!--k) {
        for (int u = 0; u < n; u++) cout << a[u] << ' ';
        return cout << '\n', void();
      }
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
