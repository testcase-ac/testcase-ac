#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> egraph[10001];
vector<int> rgraph[10001];

pii times[10001];
int tick = 0;
int cc = 0;
int vis[10001];

void clock_dfs(int v) {
  vis[v] = 1;
  tick++;

  for (auto dst: rgraph[v]) {
    if (!vis[dst]) clock_dfs(dst);
  }
  times[v] = {++tick, v};
}

void dfs(int v) {
  vis[v] = 1;
  for (auto dst: egraph[v]) {
    if (!vis[dst]) dfs(dst);
  }
}

int main() {
  fast_io();

  int n, m, v, w, p;
  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;

    for (int i = 1; i <= n; i++) {
      egraph[i].clear();
      rgraph[i].clear();
    }

    memset(vis, 0, sizeof(vis));
    while (m--) {
      cin >> v >> w >> p;
      egraph[v].push_back(w);
      rgraph[w].push_back(v);

      if (p == 2) {
        egraph[w].push_back(v);
        rgraph[v].push_back(w);
      }
    }

    for (int i = 1; i <= n; i++) {
      if (!vis[i]) clock_dfs(i);
    }

    memset(vis, 0, sizeof(vis));
    sort(times + 1, times + n + 1);
    dfs(times[n].second);

    bool able = true;
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) able = false;
    }
    cout << able << '\n';
  }
}
