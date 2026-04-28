#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 64;
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
char board_A[MAXN + 1][MAXN + 1], board_B[MAXN + 1][MAXN + 1];
int board[MAXN + 1][MAXN + 1];
bool vis[MAXN + 1][MAXN + 1][4];

void solve() {
  int H, W, ci, cj, dir; cin >> H >> W >> ci >> cj >> dir;
  for (int i = 0; i < H; ++i) cin >> board_A[i];
  for (int i = 0; i < H; ++i) cin >> board_B[i];

  auto oob = [&](int i, int j) -> bool {
    return i < 0 || i >= H || j < 0 || j >= W;
  };

  int ans = 0;
  vis[ci][cj][0] = true;

  while (1) {
    int ndir, ni, nj;
    ++ans;

    if (board[ci][cj] == 0) {
      board[ci][cj] = 1;
      ndir = (dir + (board_A[ci][cj] - '0')) % 4;
    }
    else {
      ndir = (dir + (board_B[ci][cj] - '0')) % 4;
    }

    dir = ndir;
    ni = ci + dx[ndir], nj = cj + dy[ndir];
    if (oob(ni, nj)) break;
    if (board[ni][nj] == 1 && vis[ni][nj][ndir]) break;

    ci = ni, cj = nj;
    vis[ci][cj][dir] = true;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
