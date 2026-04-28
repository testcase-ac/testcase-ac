#include <bits/stdc++.h>
#define psi pair<string, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[1001][1001];
int main() {
  fast_io();

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> board[i];
  }

  int hx, hy;
  for (int i = 1; i < n - 1; i++) {
    for (int j = 1; j < n - 1; j++) {
      if (
        board[i][j - 1] == '*' &&
        board[i][j + 1] == '*' &&
        board[i - 1][j] == '*' &&
        board[i + 1][j] == '*'
      ) {
        hx = i;
        hy = j;
        cout << hx + 1 << ' ' << hy + 1 << '\n';
        break;
      }
    }
  }

  int hyl = 0, hyr = 0, hxl = 0, hll = 0, hlr = 0;
  while (hy - 1 - hyl >= 0 && board[hx][hy - 1 - hyl] == '*') hyl++;
  while (hy + 1 + hyr <= n - 1 && board[hx][hy + 1 + hyr] == '*') hyr++;
  while (hx + 1 + hxl <= n - 1 && board[hx + 1 + hxl][hy] == '*') hxl++;
  while (hx + 1 + hxl + hll <= n - 1 && board[hx + 1 + hxl + hll][hy - 1] == '*') hll++;
  while (hx + 1 + hxl + hlr <= n - 1 && board[hx + 1 + hxl + hlr][hy + 1] == '*') hlr++;
  cout << hyl << ' ' << hyr << ' ' << hxl << ' ' << hll << ' ' << hlr << '\n';
}
