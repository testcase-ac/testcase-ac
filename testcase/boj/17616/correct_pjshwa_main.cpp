#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1], ginv[MAX + 1];
bool vis1[MAX + 1], vis2[MAX + 1];

void dfsr(int v) {
  vis1[v] = true;
  for (int u : graph[v]) {
    if (!vis1[u]) dfsr(u);
  }
}

void dfsi(int v) {
  vis2[v] = true;
  for (int u : ginv[v]) {
    if (!vis2[u]) dfsi(u);
  }
}

void solve() {
  int n, m, x;
  cin >> n >> m >> x;

  while (m--) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    ginv[b].push_back(a);
  }

  dfsr(x);
  dfsi(x);
  int bwd = accumulate(vis1, vis1 + n + 1, 0) - 1;
  int fwd = accumulate(vis2, vis2 + n + 1, 0) - 1;

  cout << fwd + 1 << ' ' << n - bwd << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
