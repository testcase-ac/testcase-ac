#include <bits/stdc++.h>
using namespace std;

const int MAX = 15;
int d[MAX][MAX];
char board[MAX + 1][MAX + 1];

int main() {
  int r, c;
  cin >> r >> c;
  for (int i = 0; i < r; i++) cin >> board[i];

  d[0][0] = 1;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
    for (int k = 0; k < i; k++) for (int l = 0; l < j; l++) {
      if (board[i][j] == board[k][l]) continue;
      d[i][j] += d[k][l];
    }
  }

  cout << d[r - 1][c - 1] << '\n';
}
