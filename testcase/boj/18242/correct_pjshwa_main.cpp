#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  int xmin = M, xmax = -1, ymin = N, ymax = -1;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == '#') {
      xmin = min(xmin, j);
      xmax = max(xmax, j);
      ymin = min(ymin, i);
      ymax = max(ymax, i);
    }
  }

  int xmid = (xmin + xmax) / 2, ymid = (ymin + ymax) / 2;
  if (board[ymid][xmin] == '.') cout << "LEFT\n";
  if (board[ymid][xmax] == '.') cout << "RIGHT\n";
  if (board[ymin][xmid] == '.') cout << "UP\n";
  if (board[ymax][xmid] == '.') cout << "DOWN\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
