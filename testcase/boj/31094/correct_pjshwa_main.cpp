#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<tii> adj[MAXN + 1];
int parent[MAXN + 1][20], ZC[MAXN + 1][20], level[MAXN + 1], Z[MAXN + 1];
ll R[MAXN + 1][20];

void dfs(int v, int p, int l) {
  level[v] = l;
  for (auto [u, r, z] : adj[v]) {
    if (u == p) continue;
    parent[u][0] = v;
    R[u][0] = r;
    Z[u] = z;
    ZC[u][0] = z > 1;
    dfs(u, v, l + 1);
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

ll sum_R(int u, int p) {
  ll ret = 0;
  for (int i = 19; i >= 0; i--) {
    if (parent[u][i] == 0 || level[parent[u][i]] <= level[p]) continue;

    ret += R[u][i];
    u = parent[u][i];
  }
  return ret + R[u][0];
}

ll sum_ZC(int u, int p) {
  ll ret = 0;
  for (int i = 19; i >= 0; i--) {
    if (parent[u][i] == 0 || level[parent[u][i]] <= level[p]) continue;

    ret += ZC[u][i];
    u = parent[u][i];
  }
  return ret + ZC[u][0];
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int x, y, r, z; cin >> x >> y >> r >> z;
    adj[x].emplace_back(y, r, z);
    adj[y].emplace_back(x, r, z);
  }

  dfs(1, 0, 0);
  for (int j = 0; j < 20; j++) for (int i = 2; i <= N; i++) {
    if (parent[i][j] == 0) continue;
    parent[i][j + 1] = parent[parent[i][j]][j];
    R[i][j + 1] = R[i][j] + R[parent[i][j]][j];
    ZC[i][j + 1] = ZC[i][j] + ZC[parent[i][j]][j];
  }

  int Q; cin >> Q;
  while (Q--) {
    int a, b; ll e; cin >> a >> b >> e;
    int l = lca(a, b);

    int ZC_a = sum_ZC(a, l), ZC_b = sum_ZC(b, l);
    if (ZC_a + ZC_b > 60) {
      cout << "0\n";
      continue;
    }

    // for path a->l, find all checkpoints s.t. ZC increases
    int cur_a = a;
    for (int i = 0; i <= ZC_a && cur_a != l; ++i) {
      int u = cur_a; ll Rs = 0;
      for (int j = 19; j >= 0; --j) {
        if (parent[u][j] == 0 || level[parent[u][j]] <= level[l]) continue;
        if (ZC[u][j] > 0) continue;
        Rs += R[u][j];
        u = parent[u][j];
      }
      Rs += R[u][0];
      e = max(0LL, e - Rs) / Z[u];
      cur_a = parent[u][0];
    }

    // for path b->l, find all checkpoints s.t. ZC increases
    int cur_b = b;
    stack<pair<ll, ll>> traj;

    ll lzu = 1, lrs = 0;
    for (int i = 0; i <= ZC_b && cur_b != l; ++i) {
      int u = cur_b; ll Rs = lrs;
      for (int j = 19; j >= 0; --j) {
        if (parent[u][j] == 0 || level[parent[u][j]] <= level[l]) continue;
        if (ZC[u][j] > 0) continue;
        Rs += R[u][j];
        u = parent[u][j];
      }
      traj.emplace(Rs, lzu);
      cur_b = parent[u][0];
      lzu = Z[u], lrs = R[u][0];
    }
    traj.emplace(lrs, lzu);

    while (!traj.empty()) {
      auto [Rs, zu] = traj.top(); traj.pop();
      e = max(0LL, e - Rs) / zu;
    }
    cout << e << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
