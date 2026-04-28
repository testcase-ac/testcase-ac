#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXL = 1 << 7;
int k, x, y, it, board[MAXL][MAXL];

// Fill methods:
// 0: xo  1: ox  2: oo  3: oo
//    oo     oo     xo     ox

void rec_fill(int k, int si, int sj, int method) {
  if (k == 1) {
    int val = ++it;
    for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
      if (2 * i + j == method) continue;
      board[si + i][sj + j] = val;
    }
    return;
  }

  int l = (1 << k) / 2, h = l / 2;
  switch (method) {
  case 0:
    rec_fill(k - 1, si + h, sj + h, 0);
    rec_fill(k - 1, si + l, sj + l, 0);
    rec_fill(k - 1, si + 0, sj + l, 2);
    rec_fill(k - 1, si + l, sj + 0, 1);
    break;
  case 1:
    rec_fill(k - 1, si + h, sj + h, 1);
    rec_fill(k - 1, si + l, sj + 0, 1);
    rec_fill(k - 1, si + l, sj + l, 0);
    rec_fill(k - 1, si + 0, sj + 0, 3);
    break;
  case 2:
    rec_fill(k - 1, si + h, sj + h, 2);
    rec_fill(k - 1, si + 0, sj + l, 2);
    rec_fill(k - 1, si + 0, sj + 0, 3);
    rec_fill(k - 1, si + l, sj + l, 0);
    break;
  case 3:
    rec_fill(k - 1, si + h, sj + h, 3);
    rec_fill(k - 1, si + 0, sj + 0, 3);
    rec_fill(k - 1, si + 0, sj + l, 2);
    rec_fill(k - 1, si + l, sj + 0, 1);
    break;
  }
}

void rec_seek(int k, int si, int sj) {
  int l = (1 << k) / 2, m;
  for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
    int s = si + i * l, t = sj + j * l;
    if (s <= x && x < s + l && t <= y && y < t + l) {
      m = 2 * i + j;
      if (k > 1) rec_seek(k - 1, s, t);
    }
  }
  rec_fill(k, si, sj, m);
}

void solve() {
  cin >> k >> y >> x;
  memset(board, -1, sizeof(board));

  int N = 1 << k;
  x = N - x; y -= 1;
  rec_seek(k, 0, 0);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cout << board[i][j] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
