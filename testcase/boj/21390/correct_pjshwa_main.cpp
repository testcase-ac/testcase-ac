#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];
double d[MAX + 1][MAX + 1];
int N, M;

double r(int i, int j) {
  if (d[i][j] != -1) return d[i][j];

  double ret;
  if (board[i][j] == '.') {
    if (i == N - 1) ret = 0;
    else ret = r(i + 1, j);
  }
  else {
    if ('1' <= board[i][j] && board[i][j] <= '9') ret = board[i][j] - '0';
    else {
      if (i == N - 1) ret = 0;
      else ret = (r(i + 1, j - 1) + r(i + 1, j + 1)) / 2;
    }
  }

  return d[i][j] = ret;
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    fill(d[i], d[i] + M, -1);
  }

  double ans = 0;
  for (int j = 0; j < M; j++) ans = max(ans, r(0, j));
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
