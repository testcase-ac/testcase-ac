#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
char board[MAX + 1][MAX + 1];

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];

  vector<int> V;
  for (int j = 0; j < n; j++) {
    bool v = true;
    for (int i = 0; i < n; i++) {
      if (board[i][j] == 'W') v = false;
    }
    if (v) V.push_back(j);
  }

  reverse(V.begin(), V.end());
  for (int i = 0; i < n; i++) {
    bool v = true;
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 'W') v = false;
    }
    if (!v) continue;

    board[i][V.back()] = 'W';
    V.pop_back();
  }

  for (int i = 0; i < n; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
