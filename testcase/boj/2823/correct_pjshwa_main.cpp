#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const pii dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char board[11][11];
int R, C;

bool movable(int i, int j) {
  return i >= 0 && i < R && j >= 0 && j < C && board[i][j] == '.';
}

int main() {
  fast_io();

  cin >> R >> C;
  for (int i = 0; i < R; i++) cin >> board[i];

  int dx, dy;
  bool unable = false;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (!movable(i, j)) continue;

      int cnt = 0;
      for (int k = 0; k < 4; k++) {
        tie(dx, dy) = dirs[k];
        if (movable(i + dx, j + dy)) cnt++;
      }

      if (cnt == 1) {
        unable = true;
        break;
      }
    }
  }

  cout << unable;
}
