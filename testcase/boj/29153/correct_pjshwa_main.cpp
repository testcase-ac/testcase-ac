#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 15000;
vector<int> adj[MAXN], adj_s[MAXN];
int ma[MAXN], mb[MAXN], deg[MAXN], P[MAXN];
bool vis[MAXN];

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

bool dfs(int a) {
  vis[a] = true;
  for (int b : adj_s[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void dfs_parity(int v, int parity) {
  vis[v] = true; P[v] = parity;
  for (int u : adj_s[v]) {
    if (!vis[u]) dfs_parity(u, parity ^ 1);
  }
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v; --u; --v;
    adj[u].push_back(v); adj[v].push_back(u);
    ++deg[u]; ++deg[v];
  }

  vector<int> C;
  for (int i = 0; i < N; ++i) {
    if (deg[i] >= 3) C.push_back(i);
    else if (deg[i] == 2) {
      int a = adj[i][0], b = adj[i][1];
      assert(deg[a] >= 3 && deg[b] >= 3);
      adj_s[a].push_back(b); adj_s[b].push_back(a);
    }
  }
  for (int c : C) compress(adj_s[c]);
  for (int c : C) {
    if (!vis[c]) dfs_parity(c, 0);
  }

  memset(ma, -1, sizeof(ma));
  memset(mb, -1, sizeof(mb));

  int Z = C.size(), match = 0;
  for (int c : C) {
    if (ma[c] != -1 || P[c]) continue;
    fill(vis, vis + N, false);
    if (dfs(c)) ++match;
  }
  cout << Z - match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
