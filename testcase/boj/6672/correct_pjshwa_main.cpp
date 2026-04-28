#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4;
vector<int> adj[MAXN];

int N, M;
void solve() {
  for (int i = 0; i < N; ++i) adj[i].clear();
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }
}

int main() {
  fast_io();

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
