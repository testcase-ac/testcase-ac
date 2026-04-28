#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
char board[MAX + 1][MAX + 1];
int score[MAX][MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];

  bool init;
  int streak;
  for (int i = 0; i < n; i++) {
    init = streak = 0;
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 'B') {
        init = true;
        streak = 0;
      }
      if (board[i][j] == 'W' && init) streak++;
      if (board[i][j] == '.' && init) {
        score[i][j] += streak;
        init = false;
        streak = 0;
      }
    }

    init = streak = 0;
    for (int j = n - 1; j >= 0; j--) {
      if (board[i][j] == 'B') {
        init = true;
        streak = 0;
      }
      if (board[i][j] == 'W' && init) streak++;
      if (board[i][j] == '.' && init) {
        score[i][j] += streak;
        init = false;
        streak = 0;
      }
    }
  }

  for (int j = 0; j < n; j++) {
    init = streak = 0;
    for (int i = 0; i < n; i++) {
      if (board[i][j] == 'B') {
        init = true;
        streak = 0;
      }
      if (board[i][j] == 'W' && init) streak++;
      if (board[i][j] == '.' && init) {
        score[i][j] += streak;
        init = false;
        streak = 0;
      }
    }

    init = streak = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (board[i][j] == 'B') {
        init = true;
        streak = 0;
      }
      if (board[i][j] == 'W' && init) streak++;
      if (board[i][j] == '.' && init) {
        score[i][j] += streak;
        init = false;
        streak = 0;
      }
    }
  }

  // Diagonal
  for (int i = -n + 1; i < n; i++) {
    init = streak = 0;
    for (int j = 0; j < n; j++) {
      if (i + j < 0 || i + j >= n) continue;
      if (board[i + j][j] == 'B') {
        init = true;
        streak = 0;
      }
      if (board[i + j][j] == 'W' && init) streak++;
      if (board[i + j][j] == '.' && init) {
        score[i + j][j] += streak;
        init = false;
        streak = 0;
      }
    }

    init = streak = 0;
    for (int j = n - 1; j >= 0; j--) {
      if (i + j < 0 || i + j >= n) continue;
      if (board[i + j][j] == 'B') {
        init = true;
        streak = 0;
      }
      if (board[i + j][j] == 'W' && init) streak++;
      if (board[i + j][j] == '.' && init) {
        score[i + j][j] += streak;
        init = false;
        streak = 0;
      }
    }
  }

  for (int i = -n + 1; i < n; i++) {
    init = streak = 0;
    for (int j = 0; j < n; j++) {
      if (i + j < 0 || i + j >= n) continue;
      if (board[i + j][n - 1 - j] == 'B') {
        init = true;
        streak = 0;
      }
      if (board[i + j][n - 1 - j] == 'W' && init) streak++;
      if (board[i + j][n - 1 - j] == '.' && init) {
        score[i + j][n - 1 - j] += streak;
        init = false;
        streak = 0;
      }
    }

    init = streak = 0;
    for (int j = n - 1; j >= 0; j--) {
      if (i + j < 0 || i + j >= n) continue;
      if (board[i + j][n - 1 - j] == 'B') {
        init = true;
        streak = 0;
      }
      if (board[i + j][n - 1 - j] == 'W' && init) streak++;
      if (board[i + j][n - 1 - j] == '.' && init) {
        score[i + j][n - 1 - j] += streak;
        init = false;
        streak = 0;
      }
    }
  }

  int ms = 0, mi = -1, mj = -1;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == '.' && score[i][j] > ms) {
      ms = score[i][j];
      mi = i;
      mj = j;
    }
  }
  if (ms) cout << mj << ' ' << mi << '\n' << ms << '\n';
  else cout << "PASS\n";
}
