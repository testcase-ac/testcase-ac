#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int board[7][7], oboard[7][7];
bool marked[7][7];

void copy() {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      board[i][j] = oboard[i][j];
    }
  }
}

void drop() {
  for (int k = 0; k < 7; k++) {
    for (int i = 6; i >= 1; i--) for (int j = 0; j < 7; j++) {
      if (board[i][j] == 0 && board[i - 1][j] != 0) swap(board[i][j], board[i - 1][j]);
    }
  }
}

void mark() {
  memset(marked, 0, sizeof(marked));

  for (int i = 0; i < 7; i++) {
    int streak = 0;
    for (int j = 0; j < 7; j++) {
      if (board[i][j] == 0) {
        for (int k = j - streak; k < j; k++) {
          if (board[i][k] == streak) marked[i][k] = true;
        }
        streak = 0;
      }
      else streak++;
    }

    for (int k = 7 - streak; k < 7; k++) {
      if (board[i][k] == streak) marked[i][k] = true;
    }
  }

  for (int j = 0; j < 7; j++) {
    int streak = 0;
    for (int i = 0; i < 7; i++) {
      if (board[i][j] == 0) {
        for (int k = i - streak; k < i; k++) {
          if (board[k][j] == streak) marked[k][j] = true;
        }
        streak = 0;
      }
      else streak++;
    }

    for (int k = 7 - streak; k < 7; k++) {
      if (board[k][j] == streak) marked[k][j] = true;
    }
  }
}

int erase() {
  int cnt = 0;
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (marked[i][j]) {
        board[i][j] = 0;
        cnt++;
      }
    }
  }
  return cnt;
}

int count() {
  int cnt = 0;
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (board[i][j] != 0) cnt++;
    }
  }
  return cnt;
}

void print() {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      cout << board[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

void solve() {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      cin >> oboard[i][j];
    }
  }
  int k;
  cin >> k;

  int ans = 49;
  for (int j = 0; j < 7; j++) {
    copy();
    board[0][j] = k;
    drop();

    while (1) {
      mark();
      int res = erase();
      if (res == 0) break;
      drop();
    }

    ans = min(ans, count());
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
