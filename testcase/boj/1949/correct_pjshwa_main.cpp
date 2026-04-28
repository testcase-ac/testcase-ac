#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int val[MAX + 1], d[MAX + 1][2];
bool inc[MAX + 1];
vector<int> graph[MAX + 1], tree[MAX + 1], ans;

void construct_tree(int node, int parent) {
  tree[parent].push_back(node);
  for (int& dst : graph[node]) {
    if (dst != parent) construct_tree(dst, node);
  }
}

int dfs(int v, bool selected) {
  if (d[v][selected] == -1) {
    int ans = 0;
    if (selected) {
      ans += val[v];
      for (int& dst : tree[v]) ans += dfs(dst, 0);
    }
    else {
      for (int& dst : tree[v]) {
        int r0 = dfs(dst, 0);
        int r1 = dfs(dst, 1);
        if (r1 > r0) inc[dst] = true;
        ans += max(r0, r1);
      }
    }

    d[v][selected] = ans;
  }
  return d[v][selected];
}

void track(int v, bool selected) {
  if (selected) ans.push_back(v);
  for (int d : tree[v]) track(d, !selected && inc[d]);
}

int main() {
  fast_io();

  int n, m, a, b;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> val[i];
  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  construct_tree(1, 0);
  memset(d, -1, sizeof(d));
  int r0 = dfs(1, 0);
  int r1 = dfs(1, 1);
  if (r1 > r0) inc[1] = true;
  track(1, inc[1]);
  sort(ans.begin(), ans.end());

  cout << max(r0, r1) << '\n';
  // for (int el : ans) cout << el << ' ';
}
