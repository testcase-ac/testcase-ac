#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 300, MAXP = 10;
int A[MAXN + 1][MAXN + 1], P[MAXP + 1][MAXN + 1][MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) cin >> A[i][j];
  for (int p = 1; p <= MAXP; ++p) {
    for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
      P[p][i][j] = P[p][i - 1][j] + P[p][i][j - 1] - P[p][i - 1][j - 1];
      if (A[i][j] == p) ++P[p][i][j];
    }
  }

  int Q; cin >> Q;
  while (Q--) {
    int x1, y1, x2, y2, ans = 0; cin >> x1 >> y1 >> x2 >> y2;
    for (int p = 1; p <= MAXP; ++p) {
      int cnt = P[p][x2][y2] - P[p][x1 - 1][y2] - P[p][x2][y1 - 1] + P[p][x1 - 1][y1 - 1];
      ans += cnt > 0;
    }
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
