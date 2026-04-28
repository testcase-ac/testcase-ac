#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1000;
vector<int> graph[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
  }

  int a, b, k;
  cin >> a >> b >> k;
  vector<int> c(k);
  for (int i = 0; i < k; i++) cin >> c[i];

  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
