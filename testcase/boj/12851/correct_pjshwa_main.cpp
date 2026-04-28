#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5 + 1;
bool vis[MAX];
int s, e;

pii bfs() {
  queue<pii> q;
  q.push({s, 0});
  vis[s] = true;

  int mc = -1, mw = 0;
  while (!q.empty()) {
    auto [u, c] = q.front();
    q.pop();

    vis[u] = true;
    if (u == e) {
      if (mc == -1) mc = c;
      if (mc == c) mw++;
    }

    if (u - 1 >= 0 && !vis[u - 1]) q.push({u - 1, c + 1});
    if (u + 1 < MAX && !vis[u + 1]) q.push({u + 1, c + 1});
    if (u * 2 < MAX && !vis[u * 2]) q.push({u * 2, c + 1});
  }

  return {mc, mw};
}

int main() {
  fast_io();

  cin >> s >> e;
  pii res = bfs();
  cout << res.first << "\n" << res.second << "\n";
}
