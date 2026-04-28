#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 10000;
const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
int A[MAX + 1][MAX + 1];

int tc;
void solve() {
  // cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  {
    int dx = 0, dy = 1, x = 1, y = 1, t = 1;
    while (t <= N * N) {
      A[x][y] = t++;
      if (x + dx < 1 || x + dx > N || y + dy < 1 || y + dy > N || A[x + dx][y + dy]) {
        if (dx == 0 && dy == 1) dx = 1, dy = 0;
        else if (dx == 1 && dy == 0) dx = 0, dy = -1;
        else if (dx == 0 && dy == -1) dx = -1, dy = 0;
        else if (dx == -1 && dy == 0) dx = 0, dy = 1;
      }
      x += dx;
      y += dy;
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      string s = to_string(A[i][j]);
      while (s.size() < 4) s = ' ' + s;
      cout << s << ' ';
    }
    cout << '\n';
  }

  // vector<pii> cur;

  // function<void(int, int, int)> dfs = [&](int x, int y, int t) {
  //   cur.emplace_back(x, y);

  //   if (x == N / 2 + 1 && y == N / 2 + 1) {
  //     cout << "dist = " << t << '\n';
  //     for (auto& [x, y] : cur) cout << A[x][y] << ' ';
  //     cout << '\n';
  //   }
  //   else {
  //     for (int i = 0; i < 4; i++) {
  //       int nx = x + dx[i], ny = y + dy[i];
  //       if (nx < 1 || nx > N || ny < 1 || ny > N) continue;
  //       if (A[nx][ny] <= A[x][y]) continue;

  //       dfs(nx, ny, t + 1);
  //     }
  //   }
  //   cur.pop_back();

  // };
  // dfs(1, 1, 0);

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
