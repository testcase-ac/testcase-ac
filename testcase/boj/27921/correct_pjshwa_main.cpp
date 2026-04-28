#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 10;
char board1[MAX + 1][MAX + 1], board2[MAX + 1][MAX + 1];

void solve() {
  int H1, W1; cin >> H1 >> W1;
  for (int i = 0; i < H1; i++) cin >> board1[i];

  int H2, W2, siz = 0; cin >> H2 >> W2;
  for (int i = 0; i < H2; i++) {
    cin >> board2[i];
    for (int j = 0; j < W2; j++) {
      if (board2[i][j] == 'O') siz++;
    }
  }

  int ans = siz;
  for (int dx = -300; dx <= 300; dx++) for (int dy = -300; dy <= 300; dy++) {
    int ov = 0;
    for (int i = 0; i < H1; i++) for (int j = 0; j < W1; j++) {
      int ci = i + dx, cj = j + dy;
      if (ci < 0 || ci >= H2 || cj < 0 || cj >= W2) continue;

      if (board1[i][j] == 'O' && board2[ci][cj] == 'O') ov++;
    }
    ans = min(ans, siz - ov);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
