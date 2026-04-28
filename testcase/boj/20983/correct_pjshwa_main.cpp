#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
int T[MAXN + 1], vis[MAXN + 1];
vector<pii> A[MAXN + 1];

void quit() {
  cout << "-1\n";
  exit(0);
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) cin >> T[i];
  for (int i = 1; i <= M; ++i) {
    int u, a, b; cin >> u >> a >> b;
    A[u].emplace_back(a, b);
    A[a].emplace_back(u, b);
  }

  queue<pii> q;
  for (int u = 1; u <= N; ++u) {
    if (T[u] != 1) continue;

    vis[u] = 1;
    for (auto [a, b] : A[u]) q.emplace(a, b);
  }

  while (!q.empty()) {
    auto [a, b] = q.front(); q.pop();
    if (T[a] == 1) {
      if (T[b] == 2) quit();
      T[b] = 1;
      if (!vis[b]) {
        vis[b] = 1;
        for (auto [c, d] : A[b]) q.emplace(c, d);
      }
    }
    if (T[b] == 2) T[a] = 2;
  }

  for (int u = 1; u <= N; ++u) cout << min(2, T[u]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
