#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m, x, y;
  cin >> n >> m >> x >> y;

  set<int> graph[n + 1];
  while (m--) {
    int a, b;
    cin >> a >> b;
    graph[a].insert(b);
    graph[b].insert(a);
  }

  set<int> s{x};
  while (y--) {
    set<int> ns;
    for (int e : s) {
      for (int f : graph[e]) ns.insert(f);
    }
    s = ns;
  }

  if (s.size()) for (int e : s) cout << e << ' ';
  else cout << -1;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
