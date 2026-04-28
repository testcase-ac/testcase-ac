#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
bool vacant[MAX];

void solve() {
  int n, x;
  cin >> n;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < n; i++) {
    cin >> x;
    pq.push({x, i});
  }

  long long ans = 0;
  int chgt = 0, groups = 1;
  while (1) {
    while (!pq.empty() && pq.top().first <= chgt) {
      int idx = pq.top().second;
      pq.pop();
      vacant[idx] = true;
      groups++;
      if (idx == 0 || idx == n - 1) groups--;
      if (idx > 0 && vacant[idx - 1]) groups--;
      if (idx < n - 1 && vacant[idx + 1]) groups--;
    }

    chgt++;
    ans += groups;
    if (pq.empty()) break;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
