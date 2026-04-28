#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
pii graph[MAX + 1];
vector<int> level[MAX + 1];
int indegree[MAX + 1], l[MAX + 1], cl;

void dfs(int v, int lev) {
  if (graph[v].first != -1) dfs(graph[v].first, lev + 1);
  l[v] = cl++;
  level[lev].push_back(v);
  if (graph[v].second != -1) dfs(graph[v].second, lev + 1);
}

int main() {
  fast_io();

  int n, ni, nl, nr;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> ni >> nl >> nr;
    graph[ni] = {nl, nr};
    if (nl != -1) indegree[nl]++;
    if (nr != -1) indegree[nr]++;
  }

  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) dfs(i, 1);
  }

  int md = -1, ml = -1;
  for (int i = 1; i <= MAX; i++) {
    if (level[i].empty()) break;

    int mn = 2e9, mx = -2e9;
    for (int el : level[i]) {
      mn = min(mn, l[el]);
      mx = max(mx, l[el]);
    }
    int cd = mx - mn + 1;
    if (cd > md) {
      md = cd;
      ml = i;
    }
  }

  cout << ml << ' ' << md;
}
