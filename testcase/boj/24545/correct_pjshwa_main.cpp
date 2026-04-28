#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
multiset<int> blens[MAX + 1];
int dv[MAX + 1], dans[MAX + 1];
bool vis[MAX + 1];

int dfs(int v) {
  vis[v] = 1;

  int mval = 0, mvtx = -1;
  for (int d : graph[v]) {
    if (!vis[d]) {
      int dval = dfs(d);
      blens[v].insert(-dval);
      if (dval > mval) mval = dval, mvtx = d;
    }
  }

  dv[v] = mvtx;
  return mval + 1;
}

void dfs_parlen(int v, int parlen) {
  vis[v] = 1;

  blens[v].insert(-parlen);
  if (graph[v].size() >= 3) {
    auto it = blens[v].begin();
    int ans = 0;
    for (int i = 0; i < 3; i++) {
      ans += *it;
      it++;
    }
    dans[v] = -ans;
  }

  for (int d : graph[v]) {
    if (!vis[d]) {
      int mlen, bmax;
      auto it = blens[v].begin();
      if (dv[v] == d) bmax = blens[v].size() == 1 ? 0 : *(++it);
      else bmax = *it;
      mlen = max(parlen, -bmax);
      dfs_parlen(d, mlen + 1);
    }
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  memset(vis, 0, sizeof(vis));
  dfs(1);
  memset(vis, 0, sizeof(vis));
  memset(dans, -1, sizeof(dans));
  dfs_parlen(1, 0);

  cout << *max_element(dans + 1, dans + n + 1) + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
