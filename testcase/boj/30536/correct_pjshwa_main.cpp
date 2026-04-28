#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
int X[MAX], Y[MAX];
int P[MAX], R[MAX];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];
  for (int i = 0; i < M; ++i) cin >> P[i], --P[i];

  int R0; cin >> R0;
  for (int i = 0; i < M; ++i) cin >> R[i];

  vector<bool> oreach(N, false);
  for (int i = 0; i < M; ++i) {
    int ox = X[P[i]], oy = Y[P[i]];
    for (int j = 0; j < N; ++j) {
      int dx = ox - X[j], dy = oy - Y[j];
      if (dx * dx + dy * dy <= R[i] * R[i]) {
        oreach[j] = true;
      }
    }
  }

  queue<int> q;
  vector<bool> vis(N, false);
  for (int i = 0; i < N; ++i) {
    if (!oreach[i]) {
      q.push(i);
      vis[i] = true;
    }
  }

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v = 0; v < N; ++v) {
      int dx = X[u] - X[v], dy = Y[u] - Y[v];
      if (dx * dx + dy * dy <= R0 * R0 && !vis[v]) {
        q.push(v);
        vis[v] = true;
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    if (vis[i]) ++ans;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
