#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500, INF = 0x3f3f3f3f;
int d[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;

  memset(d, 0x3f, sizeof(d)); d[0][0] = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      int x; cin >> x;
      for (int l = 0; l <= M; l++) {
        if (j == l) continue;
        d[i][j] = min(d[i][j], d[i - 1][l] + x);
      }
    }
  }

  int ans = INF;
  for (int j = 1; j <= M; j++) ans = min(ans, d[N][j]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
