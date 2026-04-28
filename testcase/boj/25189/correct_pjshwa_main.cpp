#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int d1[MAX + 1][MAX + 1], d2[MAX + 1][MAX + 1];
vector<pii> graph[MAX + 1][MAX + 1], rgraph[MAX + 1][MAX + 1];
int rmin[MAX + 1], cmin[MAX + 1];

void solve() {
  int n, m, rf, cf, rh, ch;
  cin >> n >> m >> rf >> cf >> rh >> ch;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    int x;
    cin >> x;
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k] * x, nj = j + dy[k] * x;
      if (ni < 1 || ni > n || nj < 1 || nj > m) continue;

      graph[i][j].push_back({ni, nj});
      rgraph[ni][nj].push_back({i, j});
    }
  }

  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) d1[i][j] = d2[i][j] = INF;
  queue<tii> q;

  d1[rf][cf] = 0;
  q.push(make_tuple(rf, cf, 0));
  while (!q.empty()) {
    auto [i, j, c] = q.front();
    q.pop();

    for (auto [ni, nj] : graph[i][j]) {
      if (d1[ni][nj] > c + 1) {
        d1[ni][nj] = c + 1;
        q.push(make_tuple(ni, nj, c + 1));
      }
    }
  }

  d2[rh][ch] = 0;
  q.push(make_tuple(rh, ch, 0));
  while (!q.empty()) {
    auto [i, j, c] = q.front();
    q.pop();

    for (auto [ni, nj] : rgraph[i][j]) {
      if (d2[ni][nj] > c + 1) {
        d2[ni][nj] = c + 1;
        q.push(make_tuple(ni, nj, c + 1));
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    rmin[i] = d2[i][1];
    for (int j = 2; j <= m; j++) rmin[i] = min(rmin[i], d2[i][j]);
  }

  for (int j = 1; j <= m; j++) {
    cmin[j] = d2[1][j];
    for (int i = 2; i <= n; i++) cmin[j] = min(cmin[j], d2[i][j]);
  }

  int ans = (rf == rh && cf == ch) ? 0 : INF;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    ans = min(ans, d1[i][j] + 1 + min(rmin[i], cmin[j]));
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
