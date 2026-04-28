#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int board[MAX][MAX], time_op[10001];
int n;

void print_board() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j];
    }
    cout << "\n";
  }
  cout << "\n";
}

int main() {
  fast_io();

  int k;
  cin >> n >> k;
  while (k--) {
    int a, b;
    cin >> a >> b;
    board[a - 1][b - 1] = 1;
  }
  
  int l;
  cin >> l;
  while (l--) {
    int t;
    string s;
    cin >> t >> s;
    time_op[t] = s[0] == 'D' ? 1 : -1;
  }

  int dir = 1;
  queue<pair<int, int>> snake;
  pair<int, int> head(0, 0);
  board[0][0] = 2;
  snake.push(head);
  for (int t = 1; t <= 20000; t++) {
    auto [x, y] = head;
    int nx = x + dx[dir], ny = y + dy[dir];

    // Game Over
    if (nx < 0 || nx >= n || ny < 0 || ny >= n || board[nx][ny] == 2) {
      return cout << t << '\n', 0;
    }

    if (board[nx][ny] != 1) {
      auto [tx, ty] = snake.front();
      snake.pop();
      board[tx][ty] = 0;
    }
    board[nx][ny] = 2;
    head = {nx, ny};
    snake.push(head);

    if (time_op[t]) {
      if (time_op[t] == -1) dir = (dir + 1) % 4;
      else dir = (dir + 3) % 4;
    }

    // print_board();
  }
}
