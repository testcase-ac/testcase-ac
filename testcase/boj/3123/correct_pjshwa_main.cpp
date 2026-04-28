#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int B[MAXN + 1][MAXN + 1];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  while (K--) {
    int x, y; cin >> x >> y;
    B[x][y] = 1;
  }

  ld ans = 0, C = sqrt(3) / 4 + M_PI / 6;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) {
    int cnt = B[i][j] + B[i][j - 1] + B[i - 1][j] + B[i - 1][j - 1];
    if (B[i][j] && B[i - 1][j - 1]) ans += 1;
    else if (B[i][j - 1] && B[i - 1][j]) ans += 1;
    else if (cnt == 2) ans += C;
    else if (cnt == 1) ans += M_PI / 4;
  }

  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
