#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int A[MAX][MAX], D[MAX][MAX], cdist[MAX][MAX];

void solve() {
  int H, W;
  cin >> H >> W;
  for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) cin >> A[i][j];
  for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) {
    if (A[i][j] <= 0) {
      D[i][j] = 1;
      continue;
    }

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
      if (A[ni][nj] == -1) continue;
      if (A[ni][nj] <= A[i][j]) continue;

      D[i][j] = 1;
      break;
    }
  }

  priority_queue<tii> pq;
  for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) {
    if (A[i][j] == -1) cdist[i][j] = -1;
    else if (D[i][j] == 0) {
      cdist[i][j] = A[i][j];
      pq.push({A[i][j], i, j});
    }
  }

  while (!pq.empty()) {
    auto [w, ui, uj] = pq.top();
    pq.pop();

    if (w < cdist[ui][uj]) continue;

    for (int k = 0; k < 4; k++) {
      int ni = ui + dx[k], nj = uj + dy[k];
      if (ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
      if (A[ni][nj] == -1) continue;

      if (cdist[ni][nj] < w - 1) {
        cdist[ni][nj] = w - 1;
        pq.push({w - 1, ni, nj});
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) {
    if (A[i][j] != cdist[i][j]) return cout << "-1\n", void();
    if (D[i][j]) continue;
    ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
