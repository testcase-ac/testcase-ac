#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 20;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

// -2 indicates empty space
// -1 indicates obstacle
int A[MAX][MAX];
int N;

void rotate_counterclockwise() {
  int B[N][N];
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) B[i][j] = A[i][j];
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) A[i][j] = B[j][N - 1 - i];
}

void drop() {
  for (int k = 0; k < N; k++) {
    for (int i = N - 1; i >= 1; i--) for (int j = 0; j < N; j++) {
      if (A[i][j] == -1) continue;
      if (A[i][j] == -2 && A[i - 1][j] >= 0) swap(A[i][j], A[i - 1][j]);
    }
  }
}

// {i, j, score}
tii find_block() {
  int ci = -1, cj = -1, c_wcount = 0, c_total = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    if (A[i][j] <= 0) continue;

    queue<pii> q;
    bool vis[N][N]{};
    int color = A[i][j];

    q.push({i, j});
    vis[i][j] = true;

    while (!q.empty()) {
      auto [x, y] = q.front(); q.pop();

      for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
        if (vis[nx][ny]) continue;

        if (A[nx][ny] == color || A[nx][ny] == 0) {
          q.push({nx, ny});
          vis[nx][ny] = true;
        }
      }
    }

    int total = 0, wcount = 0, di = -1, dj;
    for (int x = 0; x < N; x++) for (int y = 0; y < N; y++) {
      if (vis[x][y]) {
        total++;
        if (A[x][y] == 0) wcount++;
        else if (di == -1) di = x, dj = y;
      }
    }
    if (total < 2) continue;

    if (
      total > c_total ||
      (total == c_total && wcount > c_wcount) ||
      (total == c_total && wcount == c_wcount && di > ci) ||
      (total == c_total && wcount == c_wcount && di == ci && dj > cj)
    ) {
      ci = di, cj = dj, c_total = total, c_wcount = wcount;
    }
  }

  return {ci, cj, c_total * c_total};
}

void erase_block_group(int i, int j) {
  queue<pii> q;
  int color = A[i][j];

  // Mark all blocks in the group as -2
  q.push({i, j});
  A[i][j] = -2;

  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();

    for (int k = 0; k < 4; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
      
      if (A[nx][ny] == color || A[nx][ny] == 0) {
        q.push({nx, ny});
        A[nx][ny] = -2;
      }
    }
  }
}

void print() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (A[i][j] == -2) cout << ".\t";
      else cout << A[i][j] << '\t';
    }
    cout << '\n';
  }
  cout << "====================\n";
}

void solve() {
  int M; cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> A[i][j];

  int ans = 0;
  while (1) {
    auto [ci, cj, score] = find_block();
    if (ci == -1) break;

    ans += score;
    erase_block_group(ci, cj);
    drop();
    rotate_counterclockwise();
    drop();
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
