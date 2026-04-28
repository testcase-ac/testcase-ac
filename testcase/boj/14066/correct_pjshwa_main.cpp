#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char board[320][320];
int heights[51][51], n, m;
int pw, ph;

void draw(int i, int j, int h) {
  int x = 3 * h + 2 * (n - 1 - i);
  int y = 2 * (n - 1 - i) + 4 * j;
  board[x][y] = board[x + 3][y] = board[x][y + 4] = board[x + 3][y + 4] = '+';
  board[x + 5][y + 2] = board[x + 2][y + 6] = board[x + 5][y + 6] = '+';
  board[x + 1][y] = board[x + 2][y] = board[x + 1][y + 4] = board[x + 2][y + 4] = '|';
  board[x + 3][y + 6] = board[x + 4][y + 6] = '|';
  board[x + 1][y + 5] = board[x + 4][y + 5] = board[x + 4][y + 1] = '/';
  board[x][y + 1] = board[x][y + 2] = board[x][y + 3] = '-';
  board[x + 3][y + 1] = board[x + 3][y + 2] = board[x + 3][y + 3] = '-';
  board[x + 5][y + 3] = board[x + 5][y + 4] = board[x + 5][y + 5] = '-';
  board[x + 1][y + 1] = board[x + 1][y + 2] = board[x + 1][y + 3] = ' ';
  board[x + 2][y + 1] = board[x + 2][y + 2] = board[x + 2][y + 3] = ' ';
  board[x + 2][y + 5] = board[x + 3][y + 5] = ' ';
  board[x + 4][y + 2] = board[x + 4][y + 3] = board[x + 4][y + 4] = ' ';

  ph = max(ph, x + 5);
  pw = max(pw, y + 6);
}

int main() {
  fast_io();

  int max_height = 0;
  cin >> n >> m;

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    cin >> heights[i][j];
    max_height = max(max_height, heights[i][j]);
  }

  for (int height = 0; height < max_height; height++) {
    for (int j = 0; j < m; j++) for (int i = 0; i < n; i++) {
      if (heights[i][j] >= height + 1) draw(i, j, height);
    }
  }

  for (int i = ph; i >= 0; i--) {
    for (int j = 0; j <= pw; j++) cout << (board[i][j] ? board[i][j] : '.');
    cout << '\n';
  }

}
