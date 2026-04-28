#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int parent[MAX + 1], root[MAX + 1];
set<int> ss[MAX + 1];

int find_root(int n) {
  if (root[n] == n) return n;
  return root[n] = find_root(root[n]);
}

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 2; i <= n; i++) cin >> parent[i];
  for (int i = 1, c; i <= n; i++) cin >> c, ss[i].insert(c), root[i] = i;

  vector<pii> queries;
  for (int t = 1, x, a; t <= n + q - 1; t++) {
    cin >> x >> a;
    queries.push_back({x, a});
  }
  reverse(queries.begin(), queries.end());

  vector<int> ans;
  for (auto [x, a] : queries) {
    if (x == 1) {
      int p = parent[a];
      p = find_root(p), a = find_root(a);
      if (ss[a].size() >= ss[p].size()) swap(p, a);
      root[a] = p;
      for (auto it = ss[a].begin(); it != ss[a].end(); it++) ss[p].insert(*it);
      ss[a].clear();
    }
    else ans.push_back(ss[find_root(a)].size());
  }

  reverse(ans.begin(), ans.end());
  for (int e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
