#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
char board[MAXN + 1][MAXN + 1];

void solve() {
  int N, M = MAXN; cin >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];

  auto oob = [&](int r, int c) {
    return r < 0 || r >= N || c < 0 || c >= M;
  };

  int ans = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (i != N - 1 && j != 0) continue;

    string T = ""; int si = i, sj = j;
    while (!oob(si, sj)) {
      if (board[si][sj]) T += board[si][sj];
      si -= 1, sj += 1;
    }

    int Z = T.size(), fcnt = 0, bcnt = 0;
    for (int i = 0; i < Z; ++i) {
      if (T.substr(i, 5) == "KUMOH") ++fcnt;
      if (T.substr(i, 5) == "HOMUK") ++bcnt;
    }
    ans += max(fcnt, bcnt);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
