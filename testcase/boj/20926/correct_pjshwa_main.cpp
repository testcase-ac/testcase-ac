#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 0x3f3f3f3f;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
int cdist[MAX + 1][MAX + 1][4];
vector<tii> graph[MAX + 1][MAX + 1][4];

void solve() {
  int N, M;
  cin >> M >> N;

  int si, sj, ei, ej;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    for (int j = 0; j < M; j++) {
      if (board[i][j] == 'T') si = i, sj = j, board[i][j] = '0';
      if (board[i][j] == 'E') ei = i, ej = j, board[i][j] = '0';
    }
  }

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == 'R' || board[i][j] == 'H') continue;

    for (int pk = 0; pk < 4; pk++) {
      int ni = i + dx[pk], nj = j + dy[pk];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      int cost = board[i][j] - '0';
      if (board[ni][nj] == 'R') {
        for (int nk = 0; nk < 4; nk++) {
          if (pk == nk) continue;
          int ni = i + dx[nk], nj = j + dy[nk];
          graph[i][j][pk].push_back({ni, nj, nk, cost});
        }
      }
      else if (board[ni][nj] == 'H') {
        graph[i][j][pk].push_back({ni, nj, pk, INF});
      }
      else {
        graph[i][j][pk].push_back({ni, nj, pk, cost});
      }
    }
  }

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    for (int k = 0; k < 4; k++) cdist[i][j][k] = INF;
  }
  for (int k = 0; k < 4; k++) {
    cdist[si][sj][k] = 0;
    pq.push({0, si, sj, k});
  }

  while (!pq.empty()) {
    auto [w, ui, uj, uk] = pq.top();
    pq.pop();

    if (w > cdist[ui][uj][uk]) continue;

    for (auto [vi, vj, vk, vw] : graph[ui][uj][uk]) {
      if (cdist[vi][vj][vk] > cdist[ui][uj][uk] + vw) {
        cdist[vi][vj][vk] = cdist[ui][uj][uk] + vw;
        pq.push({cdist[vi][vj][vk], vi, vj, vk});
      }
    }
  }

  int ans = INF;
  for (int k = 0; k < 4; k++) {
    ans = min(ans, cdist[ei][ej][k]);
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
