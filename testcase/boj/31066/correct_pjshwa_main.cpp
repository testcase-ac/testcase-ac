#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 10, INF = 0x3f3f3f3f;
int cdist[MAX + 1][MAX + 1];

void solve() {
  int N, M, K; cin >> N >> M >> K;

  memset(cdist, 0x3f, sizeof(cdist));
  queue<pii> q;
  cdist[N][M] = 0; q.push({N, M});

  while (!q.empty()) {
    auto [a, b] = q.front(); q.pop();
    int c = N - a, d = M - b;

    for (int y = 1; y <= b; ++y) {
      for (int x = 1; x <= min(a, K * y); ++x) {
        int na = a - x, nb = b - y;
        if (cdist[na][nb] > cdist[a][b] + 1) {
          cdist[na][nb] = cdist[a][b] + 1;
          q.push({na, nb});
        }
      }
    }

    for (int w = 1; w <= d; ++w) {
      for (int z = 1; z <= min(c, K * w); ++z) {
        int nc = c - z, nd = d - w;
        int na = N - nc, nb = M - nd;
        if (cdist[na][nb] > cdist[a][b] + 1) {
          cdist[na][nb] = cdist[a][b] + 1;
          q.push({na, nb});
        }
      }
    }
  }

  int ans = INF;
  for (int d = 0; d <= MAX; ++d) ans = min(ans, cdist[0][d]);
  if (ans == INF) ans = -1;
  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
