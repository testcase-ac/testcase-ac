#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
char board[MAXN + 1][MAXN + 1];

void solve() {
  int r, c, rr, cr, rb, cb; cin >> r >> c >> rr >> cr >> rb >> cb;
  // cout << "r = " << r << ", c = " << c << ", rr = " << rr << ", cr = " << cr << ", rb = " << rb << ", cb = " << cb << endl;
  if ((r * c) & 1) return cout << "IMPOSSIBLE\n", void();

  int inv = 0;
  if (c & 1) swap(r, c), swap(rr, cr), swap(rb, cb), inv = 1;

  auto in_r = [&](int i, int j, int w, int h) {
    if (j <= c / 2) {
      if (j <= c / 2 - w) return true;
      else return i > h;
    } else {
      if (j > c / 2 + w) return false;
      else return i > r - h;
    }
  };

  int answ = -1, ansh, ans_inv = 0;
  for (int w = 0; w <= c / 2; ++w) for (int h = 0; h <= r; ++h) {
    if (answ != -1) break;
    if (in_r(rr, cr, w, h) && !in_r(rb, cb, w, h)) answ = w, ansh = h, ans_inv = 0;
    else if (!in_r(rr, cr, w, h) && in_r(rb, cb, w, h)) answ = w, ansh = h, ans_inv = 1;
  }
  assert(answ != -1);

  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      if (in_r(i, j, answ, ansh) ^ ans_inv) board[i - 1][j - 1] = 'R';
      else board[i - 1][j - 1] = 'B';
    }
  }
  if (ansh == r) {
    for (int j = 1; j <= c / 2; ++j) {
      board[0][j - 1] = 'R';
      board[r - 1][c - j] = 'B';
      if (ans_inv) swap(board[0][j - 1], board[r - 1][c - j]);
    }
  }

  if (board[rr - 1][cr - 1] == 'R' && board[rb - 1][cb - 1] == 'B') {
    if (inv) {
      for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j) cout << board[j][i];
        cout << '\n';
      }
    } else {
      for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) cout << board[i][j];
        cout << '\n';
      }
    }
  } else {
    assert(r == 1);
    cout << "IMPOSSIBLE\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
