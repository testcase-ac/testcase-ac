#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
ll a[MAX + 1], offset[MAX + 1];
bool neg[MAX + 1], vist[MAX + 1], vism[MAX + 1];
vector<pair<int, ll>> graph[MAX + 1];
ll val;
bool flag;

void dfs(int i) {
  vist[i] = 1;
  for (auto [d, w] : graph[i]) {
    if (vist[d]) {
      ll a = offset[d], b = offset[i];
      if (neg[d] == 0 && neg[i] == 0) flag = 1, val = (w - a - b) / 2;
      if (neg[d] == 1 && neg[i] == 1) flag = 1, val = (a + b - w) / 2;
    }
    else {
      neg[d] = !neg[i];
      offset[d] = w - offset[i];
      dfs(d);
    }
  }
}

void dfs_mark(int i, ll v) {
  vism[i] = 1;
  a[i] = v;
  for (auto [d, w] : graph[i]) {
    if (!vism[d]) dfs_mark(d, w - v);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int a, b, w;
    cin >> a >> b >> w;
    graph[a].emplace_back(b, w);
    graph[b].emplace_back(a, w);
  }

  for (int i = 1; i <= n; i++) {
    if (vist[i]) continue;
    flag = 0;
    dfs(i);

    if (flag) dfs_mark(i, val);
    else return cout << "ERROR\n", void();
  }

  for (int i = 1; i <= n; i++) cout << a[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
