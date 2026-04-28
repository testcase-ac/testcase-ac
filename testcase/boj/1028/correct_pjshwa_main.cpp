#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[751][751];
int ul[751][751], ur[751][751], dl[751][751], dr[751][751];
int main() {
  fast_io();

  int r, c;
  cin >> r >> c;

  for (int i = 0; i < r; i++) cin >> board[i];
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (i > 0 && j > 0 && board[i][j] == '1') dr[i][j] = dr[i - 1][j - 1] + 1;
      else dr[i][j] = board[i][j] == '1';

      if (i > 0 && j < c - 1 && board[i][j] == '1') dl[i][j] = dl[i - 1][j + 1] + 1;
      else dl[i][j] = board[i][j] == '1';
    }
  }
  for (int i = r - 1; i >= 0; i--) {
    for (int j = 0; j < c; j++) {
      if (i < r - 1 && j > 0 && board[i][j] == '1') ur[i][j] = ur[i + 1][j - 1] + 1;
      else ur[i][j] = board[i][j] == '1';

      if (i < r - 1 && j < c - 1 && board[i][j] == '1') ul[i][j] = ul[i + 1][j + 1] + 1;
      else ul[i][j] = board[i][j] == '1';
    }
  }

  int mk, cnt = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      mk = dl[i][j];
      for (int k = mk; k >= 1; k--) {
        if (
          ul[i][j] >= k &&
          j + 2 * k - 2 < c &&
          ur[i][j + 2 * k - 2] >= k &&
          dr[i][j + 2 * k - 2] >= k
        ) {
          cnt = max(k, cnt);
          break;
        }
      }
    }
  }
  cout << cnt << '\n';
}
