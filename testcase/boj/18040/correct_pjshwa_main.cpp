#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
const int dx[3] = {-1, -1, 0}, dy[3] = {-1, 0, -1};
char board[MAX + 1][MAX + 1];
int H[MAX + 1][MAX + 1], V[MAX + 1][MAX + 1], d[MAX + 1][MAX + 1][2];

void solve() {
  int N, M; cin >> N >> M;

  for (int i = 0; i < N; i++) {
    cin >> board[i];
    for (int j = 0; j < M; j++) for (int l = 0; l < 2; l++) {
      d[i][j][l] = 1;

      if (i == 0 || j == 0) continue;
      if (board[i][j] != board[i][j - 1]) continue;
      if (board[i - 1][j] != board[i - 1][j - 1]) continue;

      d[i][j][l] = max(
        min({d[i][j - 1][l], d[i - 1][j][l], d[i - 1][j - 1][l]}),
        min({d[i][j - 1][l], d[i - 1][j][1 - l], d[i - 1][j - 1][1 - l]})
      ) + 1;
    }
  }

  int ans = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) for (int l = 0; l < 2; l++) {
    ans = max(ans, d[i][j][l]);
  }
  cout << ans * ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
