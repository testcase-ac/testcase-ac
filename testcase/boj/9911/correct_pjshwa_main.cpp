#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 30;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
char board[MAX + 1][MAX + 1];
int cdist[MAX + 1][MAX + 1][4];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  int si, sj, sd, ei, ej;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == '.' || board[i][j] == '#') continue;
    if (board[i][j] == 'F') ei = i, ej = j;
    else {
      si = i, sj = j;
      if (board[i][j] == 'N') sd = 0;
      if (board[i][j] == 'E') sd = 1;
      if (board[i][j] == 'S') sd = 2;
      if (board[i][j] == 'W') sd = 3;
    }
    board[i][j] = '#';
  }

  memset(cdist, 0x3f, sizeof(cdist));
  priority_queue<tii, vector<tii>, greater<tii>> q;
  q.push({si, sj, sd}); cdist[si][sj][sd] = 0;

  while (!q.empty()) {
    auto [ci, cj, cd] = q.top(); q.pop();

    vector<int> nds;
    for (int nd = 0; nd < 4; nd++) {
      int ni = ci + dx[nd], nj = cj + dy[nd];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] == '.') continue;

      nds.push_back(nd);
    }

    for (int nd : nds) {
      // Straight
      if (nd == cd) {
        int ni = ci + dx[nd], nj = cj + dy[nd];
        if (cdist[ni][nj][nd] > cdist[ci][cj][cd]) {
          cdist[ni][nj][nd] = cdist[ci][cj][cd];
          q.push({ni, nj, nd});
        }
      }

      // Right turn
      if (nd == (cd + 1) % 4) {
        int ni = ci + dx[nd], nj = cj + dy[nd];
        if (cdist[ni][nj][nd] > cdist[ci][cj][cd] + 5) {
          cdist[ni][nj][nd] = cdist[ci][cj][cd] + 5;
          q.push({ni, nj, nd});
        }
      }

      // Left turn
      if (nd == (cd + 3) % 4) {
        int ni = ci + dx[nd], nj = cj + dy[nd];
        if (cdist[ni][nj][nd] > cdist[ci][cj][cd] + 1) {
          cdist[ni][nj][nd] = cdist[ci][cj][cd] + 1;
          q.push({ni, nj, nd});
        }
      }

      // U-turn
      // Possible only if it's the only option
      if (nds.size() == 1 && nd == (cd + 2) % 4) {
        int ni = ci + dx[nd], nj = cj + dy[nd];
        if (cdist[ni][nj][nd] > cdist[ci][cj][cd] + 10) {
          cdist[ni][nj][nd] = cdist[ci][cj][cd] + 10;
          q.push({ni, nj, nd});
        }
      }
    }

  }

  int ans = 0x3f3f3f3f;
  for (int i = 0; i < 4; i++) ans = min(ans, cdist[ei][ej][i]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
