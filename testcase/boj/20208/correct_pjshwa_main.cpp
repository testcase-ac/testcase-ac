#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, m, h, si, sj, mxstep, vis[10][10], board[10][10];
vector<pii> milks;

int manhattan_dist(pii p1, pii p2) {
  return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

void dfs(int i, int j, int health, int step) {
  if (health >= manhattan_dist({i, j}, {si, sj})) mxstep = max(mxstep, step);

  for (auto [ni, nj] : milks) {
    int cdist = manhattan_dist({i, j}, {ni, nj});
    if (cdist <= health && !vis[ni][nj]) {
      vis[ni][nj] = 1;
      dfs(ni, nj, health - cdist + h, step + 1);
      vis[ni][nj] = 0;
    }
  }
}

int main() {
  fast_io();

  cin >> n >> m >> h;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> board[i][j];
    if (board[i][j] == 1) si = i, sj = j;
    if (board[i][j] == 2) milks.push_back(make_pair(i, j));
  }

  dfs(si, sj, m, 0);
  cout << mxstep;
}
