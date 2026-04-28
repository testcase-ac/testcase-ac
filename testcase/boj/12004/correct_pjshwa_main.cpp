#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int parent[MAX + 1], usz[MAX + 1];
vector<int> graph[MAX + 1];
bool f[MAX + 1];

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

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) parent[i] = i, usz[i] = 1;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  vector<int> queries(n);
  for (int i = 0; i < n; i++) cin >> queries[i];
  reverse(queries.begin(), queries.end());

  vector<bool> ans(n);
  for (int i = 1; i <= n; i++) {
    int x = queries[i - 1];
    for (int y : graph[x]) {
      if (f[y]) Union(x, y);
    }
    f[x] = true;

    if (usz[Find(x)] == i) ans[i - 1] = true;
    else ans[i - 1] = false;
  }

  reverse(ans.begin(), ans.end());
  for (auto e : ans) {
    if (e) cout << "YES\n";
    else cout << "NO\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
