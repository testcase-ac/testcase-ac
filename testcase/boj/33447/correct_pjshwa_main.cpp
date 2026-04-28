#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  if (N & 1) cout << "No\n";
  else {
    cout << "Yes\n";
    vector<vector<int>> ans(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N - i - 1; ++j) ans[i][j] = 1;
      for (int j = 0; j < i; ++j) ans[i][N - j - 1] = -1;
    }
    for (int i = 0; i < N; i += 2) ans[N - 1 - i][i] = 1;

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) cout << ans[i][j] << ' ';
      cout << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
