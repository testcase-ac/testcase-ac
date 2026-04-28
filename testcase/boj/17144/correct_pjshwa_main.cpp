#include <bits/stdc++.h> 
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int dust[MAX][MAX], addend[MAX][MAX];
int r, c, pr;

void op() {
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
    if (dust[i][j] != -1) dust[i][j] += addend[i][j];
    addend[i][j] = 0;
  }
}

void spread() {
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
    int cnt = 0;
    for (int k = 0; k < 4; k++) {
      int nx = i + dx[k], ny = j + dy[k];
      if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
      if (dust[nx][ny] == -1) continue;

      cnt++;
      addend[nx][ny] += dust[i][j] / 5;
    }
    addend[i][j] -= cnt * (dust[i][j] / 5);
  }
  op();
}

void dfs_ccw(int i, int j) {
  if (dust[i][j] == -1) return;

  int ni, nj;
  if (j == 0) ni = i + 1, nj = j;
  else if (i == 0) ni = i, nj = j - 1;
  else if (j == c - 1) ni = i - 1, nj = j;
  else ni = i, nj = j + 1;

  addend[ni][nj] += dust[i][j];
  addend[i][j] -= dust[i][j];
  dfs_ccw(ni, nj);
}

void dfs_cw(int i, int j) {
  if (dust[i][j] == -1) return;

  int ni, nj;
  if (j == 0) ni = i - 1, nj = j;
  else if (i == r - 1) ni = i, nj = j - 1;
  else if (j == c - 1) ni = i + 1, nj = j;
  else ni = i, nj = j + 1;

  addend[ni][nj] += dust[i][j];
  addend[i][j] -= dust[i][j];
  dfs_cw(ni, nj);
}

void purify() {
  dfs_ccw(pr - 1, 1);
  dfs_cw(pr, 1);
  op();
}

void print() {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) cout << dust[i][j] << " ";
    cout << "\n";
  }
}

int main() {
  fast_io();

  int t;
  cin >> r >> c >> t;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
    cin >> dust[i][j];
    if (dust[i][j] == -1) pr = i;
  }

  while (t--) {
    spread();
    purify();
  }

  int ans = 0;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) ans += dust[i][j];
  cout << ans + 2 << "\n";
}
