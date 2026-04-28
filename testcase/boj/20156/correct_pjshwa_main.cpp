#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int parent[MAX + 1];

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

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> t(n + 1), u(n + 1), dis(m);
  for (int i = 1; i <= n; i++) cin >> t[i], u[i] = t[i];

  for (int i = 0; i < m; i++) {
    cin >> dis[i];
    if (u[dis[i]] == -1) dis[i] = 0;
    else u[dis[i]] = -1;
  }
  for (int i = 1; i <= n; i++) parent[i] = i;
  for (int i = 1; i <= n; i++) {
    if (u[i] != -1) Union(u[i], i);
  }

  vector<tii> queries;
  for (int i = 0; i < k; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    queries.push_back({-a, b, c, i});
  }
  sort(queries.begin(), queries.end());

  vector<bool> ans(k);
  int cround = m - 1;
  for (auto [a, b, c, i] : queries) {
    while (cround >= -a) {
      if (dis[cround]) Union(dis[cround], t[dis[cround]]);
      cround--;
    }
    ans[i] = Find(b) == Find(c);
  }

  for (int i = 0; i < k; i++) {
    if (ans[i]) cout << "Same Same;\n";
    else cout << "No;\n";
  }
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
