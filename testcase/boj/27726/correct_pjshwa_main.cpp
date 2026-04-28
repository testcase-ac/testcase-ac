#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int parent1[MAX + 1], parent2[MAX + 1], parent3[MAX + 1];

int Find(int x, int parent[]) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x], parent);
}

void Union(int x, int y, int parent[]) {
  x = Find(x, parent);
  y = Find(y, parent);

  if (x != y) parent[y] = x;
}

void solve() {
  int N, M1, M2, M3; cin >> N >> M1 >> M2 >> M3;

  iota(parent1, parent1 + N + 1, 0);
  iota(parent2, parent2 + N + 1, 0);
  iota(parent3, parent3 + N + 1, 0);

  while (M1--) {
    int u, v; cin >> u >> v;
    Union(u, v, parent1);
  }
  while (M2--) {
    int u, v; cin >> u >> v;
    Union(u, v, parent2);
  }
  while (M3--) {
    int u, v; cin >> u >> v;
    Union(u, v, parent3);
  }

  map<tii, vector<int>> G;
  for (int i = 1; i <= N; i++) {
    G[{Find(i, parent1), Find(i, parent2), Find(i, parent3)}].push_back(i);
  }

  vector<vector<int>> ans;
  for (auto& [_, v] : G) {
    if (v.size() < 2) continue;
    ans.push_back(v);
  }
  sort(ans.begin(), ans.end(), [](const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
  });

  cout << ans.size() << '\n';
  for (auto& v : ans) {
    for (int x : v) cout << x << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
