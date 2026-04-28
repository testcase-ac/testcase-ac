#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
const int dx[3] = {1, 1, 1}, dy[3] = {-1, 0, 1};
int A[MAX][MAX], d[MAX][MAX][3];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> A[i][j];

  for (int i = 1; i < N; i++) for (int j = 0; j < M; j++) {
    fill(d[i][j], d[i][j] + 3, INF);
  }
  for (int j = 0; j < M; j++) {
    fill(d[0][j], d[0][j] + 3, A[0][j]);
  }

  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < 3; k++) for (int pk = 0; pk < 3; pk++) {
        int x = i + dx[k], y = j + dy[k];
        if (x < 0 || x >= N || y < 0 || y >= M) continue;
        if (k == pk) continue;

        d[x][y][k] = min(d[x][y][k], d[i][j][pk] + A[x][y]);
      }
    }
  }

  int ans = INF;
  for (int j = 0; j < M; j++) for (int k = 0; k < 3; k++) {
    ans = min(ans, d[N - 1][j][k]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
