#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m;
  cin >> n >> m;

  queue<int> q[n + 1];
  while (m--) {
    int u, v;
    cin >> u >> v;

    int o;
    if (!q[u].empty()) {
      o = q[u].front();
      q[u].pop();
    }
    else o = u;

    q[v].push(o);
    if (o == v) cout << "YES\n";
    else cout << "NO\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
