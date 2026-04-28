#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
const int dx[3] = {-1, 0, 1};
char board[MAX + 1][MAX + 1];
int D[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    D[i][0] = board[i][0] - '0';
  }

  int ans = 0;
  for (int j = 1; j < M; j++) for (int i = 0; i < N; i++) {
    int res = 0;
    for (int k = 0; k < 3; k++) {
      int pi = i + dx[k], pj = j - 1;
      if (pi < 0 || pi >= N) continue;
      res = max(res, D[pi][pj]);
    }
    ans = max(ans, res);
    D[i][j] = res + board[i][j] - '0';
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
