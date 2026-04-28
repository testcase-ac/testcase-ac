#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int h, w, c;
  cin >> h >> w >> c;

  int C[c], board[h][w];
  for (int i = 0; i < c; i++) cin >> C[i];

  int ci = 0;
  for (int i = 0; i < h; i++) {
    if (i & 1) {
      for (int j = w - 1; j >= 0; j--) {
        if (C[ci]) C[ci]--, board[i][j] = ci;
        else ci++, C[ci]--, board[i][j] = ci;
      }
    }
    else {
      for (int j = 0; j < w; j++) {
        if (C[ci]) C[ci]--, board[i][j] = ci;
        else ci++, C[ci]--, board[i][j] = ci;
      }
    }
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) cout << board[i][j] + 1;
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
