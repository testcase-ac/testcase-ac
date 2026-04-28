#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned int;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXR = 100, MAXC = 10'000, INF = 0x3f3f3f3f;
char board[MAXR + 1][MAXC + 1];

void solve() {
  int M, N;
  cin >> M >> N;

  int tw = 0;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    for (int j = 0; j < M; j++) {
      if (board[i][j] == 'W') tw++;
    }
  }

  int te = N * M - tw, cw = tw, ce = 0, cur = INF, ans = -1;
  for (int j = 0; j <= M; j++) {
    if (cur > cw + ce) {
      cur = cw + ce;
      ans = j;
    }
    if (j == M) break;

    for (int i = 0; i < N; i++) {
      if (board[i][j] == 'W') cw--;
      else ce++;
    }
  }

  cout << ans << ' ' << ans + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
