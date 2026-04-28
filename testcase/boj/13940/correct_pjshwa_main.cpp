#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
char board[MAX + 1][MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  set<pii> T;
  T.insert({0, 0});
  string ans = "";
  ans += board[0][0];

  for (int l = 1; l < N + M - 1; l++) {
    set<pii> NT;

    char lchar = 'z';
    for (int i = 0; i < N; i++) {
      int j = l - i;
      if (j < 0 || j >= M) continue;
      if (i > 0 && T.count({i - 1, j})) lchar = min(lchar, board[i][j]);
      if (j > 0 && T.count({i, j - 1})) lchar = min(lchar, board[i][j]);
    }

    for (int i = 0; i < N; i++) {
      int j = l - i;
      if (j < 0 || j >= M) continue;
      if (i > 0 && T.count({i - 1, j}) && board[i][j] == lchar) NT.insert({i, j});
      if (j > 0 && T.count({i, j - 1}) && board[i][j] == lchar) NT.insert({i, j});
    }

    ans += lchar;
    T = NT;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
