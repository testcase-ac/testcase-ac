#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXN = 1e4;
vector<int> adj[MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;

  int mdiff = 0;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
    mdiff = max(mdiff, abs(u - v));
  }
  cout << "mdiff: " << mdiff << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
