#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 700, INF = 0x3f3f3f3f;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int board[MAXN][MAXN], cdist[MAXN][MAXN];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> board[i][j];

  int l = 0, r = 1e9 + 1;
  while (l < r) {
    int m = (l + r) / 2;
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cdist[i][j] = INF;

    deque<tii> dq;
    cdist[0][0] = 0; dq.emplace_back(0, 0, 0);
    while (!dq.empty()) {
      auto [x, y, cd] = dq.front(); dq.pop_front();
      if (cd > cdist[x][y]) continue;

      for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

        int nd = cd + (board[nx][ny] > m ? 1 : 0);
        if (nd >= cdist[nx][ny] || nd > K) continue;

        cdist[nx][ny] = nd;
        if (board[nx][ny] > m) dq.emplace_back(nx, ny, nd);
        else dq.emplace_front(nx, ny, nd);
      }
    }

    if (cdist[N - 1][M - 1] <= K) r = m;
    else l = m + 1;
  }

  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
