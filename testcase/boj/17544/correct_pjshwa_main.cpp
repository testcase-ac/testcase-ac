#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int H[MAX][MAX], cdist[MAX][MAX];
int R, C, K;

bool check(int l) {
  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) cdist[i][j] = INF;

  // 0-1 bfs
  deque<pii> dq;
  for (int j = 0; j < C; j++) {
    if (H[R - 1][j] >= l) {
      cdist[R - 1][j] = 0;
      dq.push_front({R - 1, j});
    }
    else {
      cdist[R - 1][j] = 1;
      dq.push_back({R - 1, j});
    }
  }

  while (!dq.empty()) {
    auto [ux, uy] = dq.front();
    dq.pop_front();

    for (int k = 0; k < 4; k++) {
      int nx = ux + dx[k], ny = uy + dy[k];
      if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;

      if (H[nx][ny] < l) {
        if (cdist[nx][ny] > cdist[ux][uy] + 1) {
          cdist[nx][ny] = cdist[ux][uy] + 1;
          dq.push_back({nx, ny});
        }
      }
      else {
        if (cdist[nx][ny] > cdist[ux][uy]) {
          cdist[nx][ny] = cdist[ux][uy];
          dq.push_front({nx, ny});
        }
      }
    }
  }

  for (int j = 0; j < C; j++) {
    if (cdist[0][j] <= K) return true;
  }
  return false;
}

void solve() {
  cin >> R >> C >> K;

  int left = INF, right = 0;
  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
    cin >> H[i][j];
    left = min(left, H[i][j]);
    right = max(right, H[i][j] + 1);
  }

  while (left < right) {
    int mid = (left + right) / 2;

    if (check(mid)) left = mid + 1;
    else right = mid;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
