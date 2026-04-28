#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> egraph[5001];
vector<int> rgraph[5001];

pii times[5001];
int tick = 0;
int vis[5001];

void clock_dfs(int v) {
  vis[v] = 1;
  tick++;

  for (auto dst: rgraph[v]) {
    if (!vis[dst]) clock_dfs(dst);
  }
  times[v] = {++tick, v};
}

void dfs_e(int v) {
  vis[v] = 1;
  for (auto dst: egraph[v]) {
    if (!vis[dst]) dfs_e(dst);
  }
}

void dfs_r(int v) {
  vis[v] = 1;
  for (auto dst: rgraph[v]) {
    if (!vis[dst]) dfs_r(dst);
  }
}

int main() {
  fast_io();

  int n, m, vi, wi;

  while (1) {
    cin >> n;
    if (!n) break;

    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) {
      egraph[i].clear();
      rgraph[i].clear();
    }

    cin >> m;
    while (m--) {
      cin >> vi >> wi;
      egraph[vi].push_back(wi);
      rgraph[wi].push_back(vi);
    }

    for (int i = 1; i <= n; i++) {
      if (!vis[i]) clock_dfs(i);
    }

    memset(vis, 0, sizeof(vis));
    sort(times + 1, times + n + 1);

    vector<int> srcs;
    for (int i = n; i >= 1; i--) {
      int vtx = times[i].second;
      if (!vis[vtx]) {
        srcs.push_back(vtx);
        dfs_r(vtx);
      }
    }

    memset(vis, 0, sizeof(vis));
    for (auto src : srcs) dfs_e(src);

    for (int i = 1; i <= n; i++) {
      if (vis[i]) cout << i << ' ';
    }
    cout << '\n';
  }
}
