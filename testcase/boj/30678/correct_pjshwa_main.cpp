#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 4000;
const int dl[] = {1, 5, 25, 125, 625, 3125};
const bool U[5][5] = {
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {1, 1, 1, 1, 1},
  {0, 1, 1, 1, 0},
  {0, 1, 0, 1, 0},
};
char board[MAX + 1][MAX + 1];

void rec(int l, int si, int sj) {
  if (l == 0) {
    board[si][sj] = '*';
    return;
  }

  for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) {
    if (!U[i][j]) continue;
    rec(l - 1, si + i * dl[l - 1], sj + j * dl[l - 1]);
  }
}

void solve() {
  int L; cin >> L;
  for (int i = 0; i < dl[L]; ++i) for (int j = 0; j < dl[L]; ++j) {
    board[i][j] = ' ';
  }

  rec(L, 0, 0);
  for (int i = 0; i < dl[L]; ++i) {
    for (int j = 0; j < dl[L]; ++j) {
      cout << board[i][j];
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
