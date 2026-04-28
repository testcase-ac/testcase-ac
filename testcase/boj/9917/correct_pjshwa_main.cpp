#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 20;
vector<int> adj[MAXN + 1];
int f, s, vis[MAXN + 1];

void dfs(int v) {
  vis[v] = 1;
  for (int u : adj[v]) {
    if (vis[u]) f |= s == u;
    else dfs(u);
  }
  vis[v] = 0;
}

void solve() {
  int N, K; cin >> N >> K;
  while (K--) {
    int a, b, sa, sb; cin >> a >> b >> sa >> sb;
    if (sa > sb) adj[a].push_back(b);
    else adj[b].push_back(a);
  }

  int ans = 0;
  for (s = 1; s <= N; ++s) {
    f = 0; dfs(s); ans += f;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
