#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
int board[MAX][MAX];

void solve() {
  int N, M, K;
  cin >> N >> M >> K;

  int cnt = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    cin >> board[i][j];
    cnt += board[i][j];
  }

  vector<pii> ans;
  map<int, int> xt, yt;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == 1) xt[i]++, yt[j]++;
  }

  // Overlapping on one row
  if (xt.size() == 1) {
    int ov = 2 * K - cnt;
    int fi = xt.begin()->first, fj = yt.begin()->first;
    for (int i = 1; i <= ov; i++) ans.push_back({fi, fj + K - i});
  }

  // Overlapping on one column
  else if (yt.size() == 1) {
    int ov = 2 * K - cnt;
    int fi = xt.begin()->first, fj = yt.begin()->first;
    for (int i = 1; i <= ov; i++) ans.push_back({fi + K - i, fj});
  }

  // Crossing each other
  else if (cnt != 2 * K) {
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
      if (xt[i] > 1 && yt[j] > 1) ans.push_back({i, j});
    }
  }

  cout << ans.size() << '\n';
  sort(ans.begin(), ans.end()); // <- This should not be necessary
  for (auto [i, j] : ans) cout << i + 1 << ' ' << j + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
