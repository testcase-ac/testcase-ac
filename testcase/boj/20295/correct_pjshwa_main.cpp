#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int C[MAX + 1];
vector<int> graph[MAX + 1];
int parent[MAX + 1][20];
int level[MAX + 1];
int lcan[6][MAX + 1];
bool vis[MAX + 1];

void dfs(int node, int lv, int ccnt, int ccan) {
  vis[node] = true;
  level[node] = lv;
  if (C[node] == ccan) ccnt++;
  lcan[ccan][node] = ccnt;

  for (int el : graph[node]) {
    if (!vis[el]) {
      parent[el][0] = node;
      dfs(el, lv + 1, ccnt, ccan);
    }
  }
}

int lca(int x, int y) {
  if (level[x] < level[y]) swap(x, y);
  int diff = level[x] - level[y];

  for (int i = 0; diff; i++) {
    if (diff % 2) x = parent[x][i];
    diff /= 2;
  }

  // level[x] = level[y] from now on.
  if (x != y) {
    for (int i = 19; i >= 0; i--) {
      if (!parent[x][i] || parent[x][i] == parent[y][i]) continue;

      x = parent[x][i];
      y = parent[y][i];
    }

    x = parent[x][0];
  }
  
  return x;
}

bool f(int from, int to, int ccan) {
  int l = lca(from, to);

  if (C[from] == ccan || C[to] == ccan || C[l] == ccan) return true;
  if (lcan[ccan][from] - lcan[ccan][l]) return true;
  if (lcan[ccan][to] - lcan[ccan][l]) return true;
  return false;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> C[i];
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  for (int c = 1; c <= 5; c++) {
    memset(vis, 0, sizeof(vis));
    dfs(1, 0, 0, c);
  }
  for (int j = 0; j < 20; j++) for (int i = 2; i <= N; i++) {
    if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];
  }

  int Q;
  cin >> Q;

  int u, c;
  cin >> u >> c;

  bool a = false;
  for (int i = 1; i <= N; i++) {
    if (f(i, u, c)) {
      cout << "PLAY\n";
      a = true;
      break;
    }
  }
  if (!a) cout << "CRY\n";

  int l = u;
  while (--Q) {
    cin >> u >> c;
    if (f(l, u, c)) cout << "PLAY\n";
    else cout << "CRY\n";
    l = u;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
