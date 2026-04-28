#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
char board[MAXN + 1][MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];

  int ans = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {

    for (int d = 0; d < 8; ++d) {
      string U;
      for (int k = 0; k < 5; ++k) {
        int ci = i + k * dx[d], cj = j + k * dy[d];
        if (ci < 0 || ci >= N || cj < 0 || cj >= N) break;
        U.push_back(board[ci][cj]);
      }
      if (U == "MOBIS") ++ans;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
