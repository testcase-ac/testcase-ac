#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
set<int> gbrk[MAX + 1];
int dist[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;

  memset(dist, -1, sizeof(dist));

  while (m--) {
    int a, b;
    cin >> a >> b;
    gbrk[a].insert(b);
    gbrk[b].insert(a);
  }

  set<int> unused;
  for (int i = 2; i <= n; i++) unused.insert(i);

  queue<int> order;
  dist[1] = 0;
  order.push(1);

  while (!order.empty()) {
    int o = order.front();
    order.pop();

    vector<int> uc{unused.begin(), unused.end()};
    for (int v : uc) {
      if (!gbrk[o].count(v)) {
        unused.erase(v);
        order.push(v);
        dist[v] = dist[o] + 1;
      }
    }
  }

  for (int i = 1; i <= n; i++) cout << dist[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
