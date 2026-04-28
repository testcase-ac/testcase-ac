#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int mod;
vector<int> graph[MAX + 1];
int parent[MAX + 1][20], level[MAX + 1];
ll v[MAX + 1][20], r[MAX + 1][20];
bool vis[MAX + 1];

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void dfs(int node, int lv) {
  vis[node] = true;
  level[node] = lv;

  for (int el : graph[node]) {
    if (!vis[el]) {
      parent[el][0] = node;
      dfs(el, lv + 1);
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

void solve() {
  int n, q;
  cin >> n >> mod >> q;
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    cin >> v[i][0];
    r[i][0] = v[i][0];
  }

  // fill parent array
  dfs(1, 0);
  for (int j = 0; j < 20; j++) for (int i = 1; i <= n; i++) {
    if (!parent[i][j]) continue;
    parent[i][j + 1] = parent[parent[i][j]][j];

    ll o, w = 1 << j;
    o = (v[i][j] * lpow(10, w, mod)) % mod;
    v[i][j + 1] = (v[parent[i][j]][j] + o) % mod;
    o = (r[parent[i][j]][j] * lpow(10, w, mod)) % mod;
    r[i][j + 1] = (r[i][j] + o) % mod;
  }

  while (q--) {
    int x, y;
    cin >> x >> y;
    int l = lca(x, y), d = level[y] - level[l];

    ll e1 = 0;
    for (int i = 19; i >= 0; i--) {
      if (!parent[x][i] || level[parent[x][i]] < level[l]) continue;
      e1 = (e1 * lpow(10, 1 << i, mod)) % mod;
      e1 = (e1 + v[x][i]) % mod;
      x = parent[x][i];
    }

    ll e2 = 0, pw = 0;
    for (int i = 19; i >= 0; i--) {
      if (!parent[y][i] || level[parent[y][i]] < level[l]) continue;
      e2 = (e2 + ((lpow(10, pw, mod) * r[y][i]) % mod)) % mod;
      y = parent[y][i];
      pw += (1 << i);
    }

    ll ans = (e1 * 10 + v[l][0]) % mod;
    ans = (ans * lpow(10, d, mod) + e2) % mod;
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
