#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5, INF = 0x3f3f3f3f;
int cdist[2][MAX + 1], T[MAX + 1];

void solve() {
  int N, K;
  cin >> N >> K;

  memset(T, -1, sizeof(T));

  T[K] = 0;
  int cur = K;
  for (int i = 1;; i++) {
    cur += i;
    if (cur > MAX) break;
    T[cur] = i;
  }

  for (int i = 0; i < 2; i++) fill(cdist[i], cdist[i] + MAX + 1, INF);
  queue<pii> q;
  q.push({0, N});
  cdist[0][N] = 0;

  while (!q.empty()) {
    auto [p, v] = q.front(); q.pop();

    if (v - 1 >= 0 && cdist[1 - p][v - 1] == INF) {
      cdist[1 - p][v - 1] = cdist[p][v] + 1;
      q.push({1 - p, v - 1});
    }
    if (v + 1 <= MAX && cdist[1 - p][v + 1] == INF) {
      cdist[1 - p][v + 1] = cdist[p][v] + 1;
      q.push({1 - p, v + 1});
    }
    if (2 * v <= MAX && cdist[1 - p][2 * v] == INF) {
      cdist[1 - p][2 * v] = cdist[p][v] + 1;
      q.push({1 - p, 2 * v});
    }
  }

  int ans = INF;
  for (int i = 0; i <= MAX; i++) {
    if (T[i] == -1) continue;

    int p = T[i] & 1;
    if (cdist[p][i] <= T[i]) ans = min(ans, T[i]);
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
