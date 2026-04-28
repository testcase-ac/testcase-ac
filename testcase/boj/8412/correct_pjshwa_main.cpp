#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int W[MAXN + 1], B[MAXN + 1];

void solve() {
  int N; cin >> N;
  vector<int> board(2 * N + 2, 1);
  board[N + 1] = board[0] = 0;

  for (int i = 1; i <= N; ++i) {
    W[i] = N + 1 - i;
    B[i] = N + 1 + i;
  }

  cout << N * (N + 2) << '\n';
  auto move_f = [&](int i) {
    cout << i << '\n';
    if (board[i + 1] == 0) {
      swap(board[i], board[i + 1]);
      return i + 1;
    }
    else if (board[i + 2] == 0) {
      swap(board[i], board[i + 2]);
      return i + 2;
    }
    else assert(false);
  };
  auto move_b = [&](int i) {
    cout << i << '\n';
    if (board[i - 1] == 0) {
      swap(board[i], board[i - 1]);
      return i - 1;
    }
    else if (board[i - 2] == 0) {
      swap(board[i], board[i - 2]);
      return i - 2;
    }
    else assert(false);
  };

  int d = 0;
  for (int i = 1; i <= N; ++i) {
    d = !d;
    for (int j = 1; j <= i; ++j) {
      if (d) W[j] = move_f(W[j]);
      else B[j] = move_b(B[j]);
    }
  }
  d = !d;
  for (int j = 1; j <= N; ++j) {
    if (d) W[j] = move_f(W[j]);
    else B[j] = move_b(B[j]);
  }
  for (int i = 1; i <= N; ++i) {
    d = !d;
    for (int j = i; j <= N; ++j) {
      if (d) W[j] = move_f(W[j]);
      else B[j] = move_b(B[j]);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
