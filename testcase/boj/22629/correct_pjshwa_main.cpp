#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
bool mark[MAX + 1];
int parent[MAX + 1], U[MAX + 1], C[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void dfs(int v, int o) {
  if (mark[v]) o = v;
  C[v] = o;
  for (int u : graph[v]) {
    U[u] = v;
    dfs(u, o);
  }
}

void solve() {
  int N, Q;
  cin >> N >> Q;
  for (int i = 2; i <= N; i++) {
    int p;
    cin >> p;
    graph[p].push_back(i);
  }

  vector<pii> queries;
  mark[1] = true;
  for (int i = 0; i < Q; i++) {
    string op; int x;
    cin >> op >> x;
    if (op == "M") {
      if (mark[x]) continue;
      mark[x] = true;
      queries.push_back({0, x});
    }
    else queries.push_back({1, x});
  }

  for (int i = 1; i <= N; i++) parent[i] = i;
  dfs(1, 1);
  for (int i = 1; i <= N; i++) Union(i, C[i]);

  reverse(queries.begin(), queries.end());
  ll ans = 0;
  for (auto [op, x] : queries) {
    if (op == 0) {
      int nc = C[Find(U[x])];
      Union(x, U[x]);
      C[Find(x)] = nc;
    }
    else ans += C[Find(x)];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
