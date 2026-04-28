#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXR = 10000, MAXC = 500;
const int dx[3] = {-1, 0, 1};
char board[MAXR + 1][MAXC + 1];
bool vis[MAXR + 1][MAXC + 1];
int N, M, ans;

bool dfs(int i, int j) {
  vis[i][j] = true;
  if (j == M - 1) {
    ans++;
    return true;
  }

  for (int k = 0; k < 3; k++) {
    int ni = i + dx[k], nj = j + 1;
    if (ni < 0 || ni >= N) continue;

    if (board[ni][nj] == 'x') continue;
    if (vis[ni][nj]) continue;
    if (dfs(ni, nj)) return true;
  }
  return false;
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  for (int i = 0; i < N; i++) dfs(i, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
