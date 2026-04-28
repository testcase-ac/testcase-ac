#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 200, INF = 0x3f3f3f3f;
int cdist[MAX + 1][MAX + 1];

void solve() {
  int S, T;
  cin >> S >> T;

  for (int i = 0; i <= MAX; i++) for (int j = 0; j <= MAX; j++) {
    cdist[i][j] = INF;
  }

  queue<tuple<int, int, int>> q;
  q.push({S, T, 0});
  cdist[S][T] = 0;

  while (!q.empty()) {
    auto [s, t, d] = q.front(); q.pop();

    if (s == t) {
      cout << d << '\n';
      return;
    }

    if (2 * s <= MAX && t + 3 <= MAX) {
      if (cdist[2 * s][t + 3] == INF) {
        cdist[2 * s][t + 3] = d + 1;
        q.push({2 * s, t + 3, d + 1});
      }
    }
    if (s + 1 <= MAX) {
      if (cdist[s + 1][t] == INF) {
        cdist[s + 1][t] = d + 1;
        q.push({s + 1, t, d + 1});
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
