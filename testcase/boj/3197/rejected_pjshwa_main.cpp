#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[1501][1501];
pii parent[1501][1501];
bool vis[1501][1501];
int R, C;

pii Find(pii x) {
  auto[i, j] = x;
  if (x == parent[i][j]) return x;
  else {
    pii p = Find(parent[i][j]);
    parent[i][j] = p;
    return p;
  }
}

void Union(pii x, pii y) {
  x = Find(x);
  y = Find(y);

  auto[i, j] = y;
  if (x != y) parent[i][j] = x;
}

void dfs_union(pii p, pii node) {
  auto[i, j] = node;
  vis[i][j] = true;
  Union(p, node);

  if (i > 0 && !vis[i - 1][j] && board[i - 1][j] == '.') dfs_union(p, {i - 1, j});
  if (i < R - 1 && !vis[i + 1][j] && board[i + 1][j] == '.') dfs_union(p, {i + 1, j});
  if (j > 0 && !vis[i][j - 1] && board[i][j - 1] == '.') dfs_union(p, {i, j - 1});
  if (j < C - 1 && !vis[i][j + 1] && board[i][j + 1] == '.') dfs_union(p, {i, j + 1});
}

int main() {
  fast_io();

  cin >> R >> C;
  vector<pii> LS;

  for (int i = 0; i < R; i++) cin >> board[i];
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      parent[i][j] = {i, j};
      if (board[i][j] == 'L') {
        LS.push_back({i, j});
        board[i][j] = '.';
      }
    }
  }

  queue<tuple<pii, pii, int>> melt;

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (!vis[i][j]) dfs_union({i, j}, {i, j});
      if (board[i][j] != 'X') continue;

      if (i > 0 && board[i - 1][j] == '.') melt.push({{i, j}, {i - 1, j}, 1});
      else if (i < R - 1 && board[i + 1][j] == '.') melt.push({{i, j}, {i + 1, j}, 1});
      else if (j > 0 && board[i][j - 1] == '.') melt.push({{i, j}, {i, j - 1}, 1});
      else if (j < C - 1 && board[i][j + 1] == '.') melt.push({{i, j}, {i, j + 1}, 1});
    }
  }

  if (Find(LS[0]) == Find(LS[1])) {
    cout << 0;
    return 0;
  }

  memset(vis, 0, sizeof vis);

  while (!melt.empty()) {
    auto[p, o, d] = melt.front();
    auto[pi, pj] = p;
    melt.pop();

    if (vis[pi][pj]) continue;
    vis[pi][pj] = true;
    board[pi][pj] = '.';
    Union(o, p);

    if (pi > 0) {
      if (board[pi - 1][pj] == '.') Union(o, {pi - 1, pj});
      else if (!vis[pi - 1][pj]) melt.push({{pi - 1, pj}, {pi, pj}, d + 1});
    }
    if (pi < R - 1) {
      if (board[pi + 1][pj] == '.') Union(o, {pi + 1, pj});
      else if (!vis[pi + 1][pj]) melt.push({{pi + 1, pj}, {pi, pj}, d + 1});
    }
    if (pj > 0) {
      if (board[pi][pj - 1] == '.') Union(o, {pi, pj - 1});
      else if (!vis[pi][pj - 1]) melt.push({{pi, pj - 1}, {pi, pj}, d + 1});
    }
    if (pj < C - 1) {
      if (board[pi][pj + 1] == '.') Union(o, {pi, pj + 1});
      else if (!vis[pi][pj + 1]) melt.push({{pi, pj + 1}, {pi, pj}, d + 1});
    }

    if (Find(LS[0]) == Find(LS[1])) {
      cout << d;
      break;
    }
  }
}
