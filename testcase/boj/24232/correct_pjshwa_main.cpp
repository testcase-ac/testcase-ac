#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<tii> graph[MAX + 1];
bool vis[MAX + 1], flip[MAX + 1];
int fcnt, mcnt = 1e9, mvtx;

void dfs(int v) {
  vis[v] = 1;
  for (auto [d, i, c] : graph[v]) {
    if (!vis[d]) {
      flip[i] ^= c;
      fcnt += c;
      dfs(d);
    }
  }
}

void dfs_mark(int v) {
  vis[v] = 1;
  if (mcnt > fcnt) {
    mcnt = fcnt;
    mvtx = v;
  }
  for (auto [d, i, c] : graph[v]) {
    if (!vis[d]) {
      if (flip[i]) {
        fcnt--;
        flip[i] ^= 1;
        dfs_mark(d);
        flip[i] ^= 1;
        fcnt++;
      }
      else {
        fcnt++;
        flip[i] ^= 1;
        dfs_mark(d);
        flip[i] ^= 1;
        fcnt--;
      }
    }
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back({b, i, 0});
    graph[b].push_back({a, i, 1});
  }

  dfs(1);
  memset(vis, 0, sizeof vis);
  dfs_mark(1);
  memset(vis, 0, sizeof vis);
  memset(flip, 0, sizeof flip);
  dfs(mvtx);
  for (int i = 0; i < n - 1; i++) cout << flip[i];
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
