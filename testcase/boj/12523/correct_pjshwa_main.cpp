#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<int> adj[MAXN + 1];
int vis[MAXN + 1], cnt;

void dfs(int v) {
  vis[v] = 1; ++cnt;
  for (int u : adj[v]) {
    if (!vis[u]) dfs(u);
  }
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ":\n";

  int N; cin >> N;
  for (int i = 1; i <= N; ++i) adj[i].clear();
  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    adj[x].push_back(i);
  }

  for (int i = 1; i <= N; ++i) {
    fill(vis, vis + N + 1, 0); cnt = 0;
    dfs(i);
    cout << cnt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
