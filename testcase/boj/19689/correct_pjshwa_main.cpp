#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int R, C, D, K; cin >> R >> C >> D >> K;

  vector<vector<int>> B(R + 1, vector<int>(C + 1));
  vector<pii> mush;
  for (int i = 0; i < R; ++i) {
    string S; cin >> S;
    for (int j = 0; j < C; ++j) {
      if (S[j] == 'M') mush.emplace_back(i, j);
      else if (S[j] == 'S') {
        int l = max(0, j - D), r = min(C - 1, j + D);
        int u = max(0, i - D), d = min(R - 1, i + D);
        ++B[u][l]; --B[u][r + 1];
        --B[d + 1][l]; ++B[d + 1][r + 1];
      }
    }
  }

  for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
    B[i][j + 1] += B[i][j];
  }
  for (int j = 0; j < C; ++j) for (int i = 0; i < R; ++i) {
    B[i + 1][j] += B[i][j];
  }

  // cout << "B =\n";
  // for (int i = 0; i < R; ++i) {
  //   for (int j = 0; j < C; ++j) cout << B[i][j] << ' ';
  //   cout << '\n';
  // }

  int ans = 0;
  for (auto [i, j] : mush) {
    if (B[i][j] >= K) ++ans;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
