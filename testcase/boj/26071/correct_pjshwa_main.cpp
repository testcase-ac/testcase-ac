#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1500;
char board[MAX + 1][MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];

  set<int> H, V;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (board[i][j] == 'G') {
      H.insert(i);
      V.insert(j);
    }
  }

  int ans = 0;
  if (H.size() > 1) {
    int mdist = min(*H.rbegin(), N - 1 - *H.begin());
    ans += mdist;
  }
  if (V.size() > 1) {
    int mdist = min(*V.rbegin(), N - 1 - *V.begin());
    ans += mdist;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
