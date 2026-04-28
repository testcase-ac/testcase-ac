#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];
int h, w;

void print_board() {
  for (int i = 0; i < h; i++) cout << board[i] << '\n';
}

void solve() {
  int n; cin >> h >> w >> n;
  int hl = (h - 1) / 2, wl = (w - 1) / 2;

  for (int i = 0; i < h; i++) fill(board[i], board[i] + w, '.');

  for (int a = 1; a * a <= n; a++) {
    if (n % a) continue;

    int b = n / a;
    if (a - 1 <= hl && b - 1 <= wl) {
      for (int i = 0; i < a - 1; i++) {
        for (int j = 0; j < w; j++) {
          board[2 * i + 1][j] = '#';
        }
      }
      for (int j = 0; j < b - 1; j++) {
        for (int i = 0; i < h; i++) {
          board[i][2 * j + 1] = '#';
        }
      }
      print_board();
      return;
    }
    else if (a - 1 <= wl && b - 1 <= hl) {
      for (int i = 0; i < b - 1; i++) {
        for (int j = 0; j < w; j++) {
          board[2 * i + 1][j] = '#';
        }
      }
      for (int j = 0; j < a - 1; j++) {
        for (int i = 0; i < h; i++) {
          board[i][2 * j + 1] = '#';
        }
      }
      print_board();
      return;
    }
  }

  cout << "Impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
