#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int K; cin >> K;
  vector<vector<char>> G(3, vector<char>(4, '.'));
  G[0][0] = 'G'; G[1][1] = 'I'; G[2][2] = 'S'; G[1][3] = 'T';

  for (int i = 0; i < 3 * K; ++i) {
    for (int j = 0; j < 4 * K; ++j) {
      cout << G[i / K][j / K];
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
