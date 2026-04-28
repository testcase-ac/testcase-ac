#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
char board[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  int l = 0, r = N;
  while (l < r) {
    int m = (l + r) / 2;

    set<string> U;
    for (int j = 0; j < M; j++) {
      string cur = "";
      for (int i = m; i < N; i++) cur += board[i][j];
      U.insert(cur);
    }

    if (U.size() == M) l = m + 1;
    else r = m;
  }

  cout << l - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
