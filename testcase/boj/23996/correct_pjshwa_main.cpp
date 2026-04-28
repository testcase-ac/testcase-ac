#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 60;
char board[MAX + 1][MAX + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];

  int rc[N]{}, cc[N]{};
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    rc[i] += (board[i][j] == 'X');
    cc[j] += (board[i][j] == 'X');
  }

  map<int, int> rtal, ctal;
  for (int i = 0; i < N; ++i) {
    rtal[rc[i]]++;
    ctal[cc[i]]++;
  }

  if (rtal[1] == 1 && rtal[2] == N - 1 && ctal[1] == 1 && ctal[2] == N - 1) {
    int oi, oj;
    for (int i = 0; i < N; ++i) if (rc[i] == 1) oi = i;
    for (int j = 0; j < N; ++j) if (cc[j] == 1) oj = j;
    if (board[oi][oj] != 'X') return cout << "IMPOSSIBLE\n", void();

    set<pii> x_row;
    for (int i = 0; i < N; ++i) {
      if (i == oi) continue;

      vector<int> x_col;
      for (int j = 0; j < N; ++j) if (board[i][j] == 'X') x_col.push_back(j);
      
      int y1 = x_col[0], y2 = x_col[1];
      if (x_row.count({y1, y2})) x_row.erase({y1, y2});
      else x_row.insert({y1, y2});
    }

    if (x_row.empty()) cout << "POSSIBLE\n";
    else cout << "IMPOSSIBLE\n";
  }
  else cout << "IMPOSSIBLE\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
