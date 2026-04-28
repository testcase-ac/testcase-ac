#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int board[MAX][MAX];
int lh[MAX][MAX], lv[MAX][MAX], lud[MAX][MAX], ldd[MAX][MAX];
int rh[MAX][MAX], rv[MAX][MAX], rud[MAX][MAX], rdd[MAX][MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  assert(2 <= n && n <= 1000);

  int bc = 0, wc = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> board[i][j];
    assert(board[i][j] == 0 || board[i][j] == 1 || board[i][j] == 2);
    if (board[i][j] == 1) bc++;
    if (board[i][j] == 2) wc++;
  }
  assert(1 <= bc && 1 <= wc);

  for (int i = 0; i < n; i++) {
    if (board[0][i] == 1) lv[0][i] = rud[0][i] = lud[0][i] = 1;
    if (board[i][0] == 1) lh[i][0] = lud[i][0] = ldd[i][0] = 1;
    if (board[n - 1][i] == 1) rv[n - 1][i] = rdd[n - 1][i] = ldd[n - 1][i] = 1;
    if (board[i][n - 1] == 1) rh[i][n - 1] = rud[i][n - 1] = rdd[i][n - 1] = 1;

    for (int j = 1; j < n; j++) {
      if (board[0][j] == 1) lh[0][j] = lh[0][j - 1] + 1;
      if (board[j][0] == 1) lv[j][0] = lv[j - 1][0] + 1;
    }

    for (int j = n - 2; j >= 0; j--) {
      if (board[n - 1][j] == 1) rh[n - 1][j] = rh[n - 1][j + 1] + 1;
      if (board[j][n - 1] == 1) rv[j][n - 1] = rv[j + 1][n - 1] + 1;
    }
  }

  for (int i = 1; i < n; i++) {
    for (int j = 1; j < n; j++) {
      if (board[i][j] == 1) {
        lv[i][j] = lv[i - 1][j] + 1;
        lh[i][j] = lh[i][j - 1] + 1;
        lud[i][j] = lud[i - 1][j - 1] + 1;
      }
    }

    for (int j = n - 2; j >= 0; j--) {
      if (board[i][j] == 1) {
        rud[i][j] = rud[i - 1][j + 1] + 1;
      }
    }
  }

  for (int i = n - 2; i >= 0; i--) {
    for (int j = n - 2; j >= 0; j--) {
      if (board[i][j] == 1) {
        rv[i][j] = rv[i + 1][j] + 1;
        rh[i][j] = rh[i][j + 1] + 1;
        rdd[i][j] = rdd[i + 1][j + 1] + 1;
      }
    }

    for (int j = 1; j < n; j++) {
      if (board[i][j] == 1) {
        ldd[i][j] = ldd[i + 1][j - 1] + 1;
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == 2) {
      int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
      if (j > 0) c1 += lh[i][j - 1];
      if (j < n - 1) c1 += rh[i][j + 1];
      if (i > 0) c2 += lv[i - 1][j];
      if (i < n - 1) c2 += rv[i + 1][j];
      if (i > 0 && j > 0) c3 += lud[i - 1][j - 1];
      if (i < n - 1 && j < n - 1) c3 += rdd[i + 1][j + 1];
      if (i < n - 1 && j > 0) c4 += ldd[i + 1][j - 1];
      if (i > 0 && j < n - 1) c4 += rud[i - 1][j + 1];

      ans = max({ans, c1, c2, c3, c4});
    }
  }
  
  cout << ans + 1 << endl;
}
