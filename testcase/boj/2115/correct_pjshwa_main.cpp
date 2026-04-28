#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[1001][1001];
int main() {
  fast_io();

  int m, n;
  cin >> m >> n;
  for (int i = 0; i < m; i++) cin >> board[i];

  int cnt = 0;
  for (int i = 0; i < m - 1; i++) {
    int uh = 0, dh = 0;
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 'X' && board[i + 1][j] == '.') {
        cnt += (uh / 2);
        uh = 0;
        dh++;
      }
      else if (board[i][j] == '.' && board[i + 1][j] == 'X') {
        cnt += (dh / 2);
        dh = 0;
        uh++;
      }
      else {
        cnt += (uh / 2);
        cnt += (dh / 2);
        uh = 0;
        dh = 0;
      }
    }
  }

  for (int j = 0; j < n - 1; j++) {
    int lv = 0, rv = 0;
    for (int i = 0; i < m; i++) {
      if (board[i][j] == 'X' && board[i][j + 1] == '.') {
        cnt += (lv / 2);
        lv = 0;
        rv++;
      }
      else if (board[i][j] == '.' && board[i][j + 1] == 'X') {
        cnt += (rv / 2);
        rv = 0;
        lv++;
      }
      else {
        cnt += (lv / 2);
        cnt += (rv / 2);
        lv = 0;
        rv = 0;
      }
    }
  }

  cout << cnt;
}
