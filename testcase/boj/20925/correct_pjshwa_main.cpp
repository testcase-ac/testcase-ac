#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200, INF = 1e9 + 7;
pii a[MAX];
int mov[MAX][MAX];

// d[i][j] = max score after time j, when we are in dungeon i
int d[MAX][1001];

void solve() {
  int n, t;
  cin >> n >> t;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> mov[i][j];

  for (int i = 0; i < n; i++) for (int j = 0; j <= t; j++) d[i][j] = -INF;
  for (int i = 0; i < n; i++) {
    if (a[i].first == 0) d[i][0] = 0;
  }

  for (int w = 1; w <= t; w++) {
    for (int from = 0; from < n; from++) {
      d[from][w] = max(d[from][w - 1] + a[from].second, d[from][w]);

      for (int to = 0; to < n; to++) {
        int mov_time = mov[from][to];
        if (mov_time > w) continue;
        if (a[to].first > d[from][w - mov_time]) continue;

        d[to][w] = max(d[to][w], d[from][w - mov_time]);
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) ans = max(ans, d[i][t]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
