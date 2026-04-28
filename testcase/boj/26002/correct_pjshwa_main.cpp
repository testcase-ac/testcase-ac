#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 40, INF = 0x3f3f3f3f;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int board[MAX][MAX];

void solve() {
  int h, w; cin >> h >> w;
  for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) cin >> board[i][j];

  int N = h * w, udist[N + 1]{};
  for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
    int dest = board[i][j];

    vector<int> adj[N + 1];
    for (int pi = 0; pi < h; ++pi) for (int pj = 0; pj < w; ++pj) {

      int mdist = INF, mdist_v = INF;
      for (int k = 0; k < 4; ++k) {
        int ni = pi + dx[k], nj = pj + dy[k];
        if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;

        mdist = min(mdist, abs(dest - board[ni][nj]));
      }

      for (int k = 0; k < 4; ++k) {
        int ni = pi + dx[k], nj = pj + dy[k];
        if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;

        if (abs(dest - board[ni][nj]) == mdist) {
          mdist_v = min(mdist_v, abs(board[pi][pj] - board[ni][nj]));
        }
      }

      for (int k = 0; k < 4; ++k) {
        int ni = pi + dx[k], nj = pj + dy[k];
        if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;

        if (abs(dest - board[ni][nj]) == mdist && abs(board[pi][pj] - board[ni][nj]) == mdist_v) {
          adj[board[ni][nj]].push_back(board[pi][pj]);
        }
      }
    }

    int cdist[N + 1]; fill(cdist, cdist + N + 1, INF);
    cdist[dest] = 0;
    queue<int> q; q.push(dest);

    while (!q.empty()) {
      int cur = q.front(); q.pop();

      for (int nxt : adj[cur]) {
        if (cdist[nxt] != INF) continue;

        cdist[nxt] = cdist[cur] + 1;
        q.push(nxt);
      }
    }

    for (int i = 1; i <= N; ++i) {
      udist[i] = max(udist[i], cdist[i]);
    }
  }

  int opt_i = -1, opt_v = INF;
  for (int i = 1; i <= N; ++i) {
    if (udist[i] < opt_v) {
      opt_i = i; opt_v = udist[i];
    }
  }

  if (opt_i == -1) cout << "impossible\n";
  else cout << opt_i << ' ' << opt_v << '\n';
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
