#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char board[1000][1000];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < 3 * n; i++) cin >> board[i];

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if ((i + j) % 2 == 0) continue;

    bool mark = false;
    int fi = 3 * i, fj = 3 * j;
    if (board[fi + 1][fj - 1] == '#') board[fi + 1][fj] = '#', mark = true;
    if (board[fi + 1][fj + 3] == '#') board[fi + 1][fj + 2] = '#', mark = true;
    if (board[fi + 3][fj + 1] == '#') board[fi + 2][fj + 1] = '#', mark = true;
    if (fi > 0 && board[fi - 1][fj + 1] == '#') board[fi][fj + 1] = '#', mark = true;
    if (mark) board[fi + 1][fj + 1] = '#';
  }

  for (int i = 0; i < 3 * n; i++) cout << board[i] << '\n';
}
