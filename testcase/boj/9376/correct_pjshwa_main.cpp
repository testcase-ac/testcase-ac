#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
int cdist1[MAX + 1][MAX + 1], cdist2[MAX + 1][MAX + 1], cdist3[MAX + 1][MAX + 1];
deque<tii> Q; int N, M;

void insert_Q(int i, int j, int cdist[MAX + 1][MAX + 1]) {
  if (board[i][j] == '*') return;

  if (board[i][j] == '#') {
    Q.push_back({i, j, 1});
    cdist[i][j] = 1;
  }
  else {
    Q.push_front({i, j, 0});
    cdist[i][j] = 0;
  }
}

// pass over the board
void bfs01(int cdist[MAX + 1][MAX + 1]) {
  while (!Q.empty()) {
    auto [i, j, w] = Q.front(); Q.pop_front();

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] == '*') continue;

      if (board[ni][nj] == '#') {
        if (cdist[ni][nj] > w + 1) {
          cdist[ni][nj] = w + 1;
          Q.push_back({ni, nj, w + 1});
        }
      }
      else {
        if (cdist[ni][nj] > w) {
          cdist[ni][nj] = w;
          Q.push_front({ni, nj, w});
        }
      }
    }
  }

}

void solve() {
  cin >> N >> M;

  memset(cdist1, 0x3f, sizeof(cdist1));
  memset(cdist2, 0x3f, sizeof(cdist2));
  memset(cdist3, 0x3f, sizeof(cdist3));

  int i1 = -1, j1, i2, j2;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    for (int j = 0; j < M; j++) {
      if (board[i][j] == '$') {
        if (i1 == -1) i1 = i, j1 = j;
        else i2 = i, j2 = j;
      }
    }
  }

  insert_Q(i1, j1, cdist1); bfs01(cdist1);
  insert_Q(i2, j2, cdist2); bfs01(cdist2);

  for (int j = 0; j < M; j++) for (int i : {0, N - 1}) insert_Q(i, j, cdist3);
  for (int i = 0; i < N; i++) for (int j : {0, M - 1}) insert_Q(i, j, cdist3);
  bfs01(cdist3);

  // There are 2 cases
  // 1. 2 prisoners make their escape separately
  // 2. 2 prisoners gather in one spot and move together

  int ans1 = INF, ans2 = INF;
  for (int j = 0; j < M; j++) for (int i : {0, N - 1}) {
    ans1 = min(ans1, cdist1[i][j]);
    ans2 = min(ans2, cdist2[i][j]);
  }
  for (int i = 0; i < N; i++) for (int j : {0, M - 1}) {
    ans1 = min(ans1, cdist1[i][j]);
    ans2 = min(ans2, cdist2[i][j]);
  }

  int ans = ans1 + ans2;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (cdist1[i][j] == INF || cdist2[i][j] == INF || cdist3[i][j] == INF) continue;

    int cur = cdist1[i][j] + cdist2[i][j] + cdist3[i][j];
    if (board[i][j] == '#') cur -= 2;
    ans = min(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
