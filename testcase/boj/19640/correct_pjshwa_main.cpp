#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
queue<tii> q[MAX];

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  for (int i = 0; i < n; i++) {
    int di, hi;
    cin >> di >> hi;
    q[i % m].push({di, hi, -(i % m), i});
  }

  priority_queue<tii> pq;
  for (int i = 0; i < m; i++) if (q[i].size()) pq.push(q[i].front()), q[i].pop();

  for (int i = 0; i < n; i++) {
    int idx = get<3>(pq.top());
    pq.pop();

    if (idx == k) return cout << i << '\n', void();
    if (q[idx % m].size()) pq.push(q[idx % m].front()), q[idx % m].pop();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
