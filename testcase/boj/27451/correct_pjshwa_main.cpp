#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 44, MAXT = 44 * 44 * 44;
vector<int> adj[MAXN];

void solve() {
  int N, M, A, B, C; cin >> N >> M >> A >> B >> C; --A; --B; --C;
  while (M--) {
    int u, v; cin >> u >> v; --u; --v;
    adj[u].push_back(v);
  }

  int S = A * N * N + B * N + C;
  vector<int> cdist(N * N * N, INT_MAX), from(N * N * N, -1);
  queue<int> q;
  cdist[S] = 0; q.push(S);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    int u1 = u / (N * N), u2 = (u / N) % N, u3 = u % N;
    for (int v1 : adj[u1]) for (int v2 : adj[u2]) for (int v3 : adj[u3]) {
      int v = v1 * N * N + v2 * N + v3;
      if (cdist[v] > cdist[u] + 1) {
        cdist[v] = cdist[u] + 1;
        from[v] = u;
        q.push(v);
      }
    }
  }

  int ans = INT_MAX, ansi = -1;
  for (int i = 0; i < N; ++i) {
    int E = i * N * N + i * N + i;
    if (ans > cdist[E]) {
      ans = cdist[E];
      ansi = i;
    }
  }
  if (ansi == -1) return cout << "-1\n", void();

  cout << ansi + 1 << ' ' << ans << '\n';

  int E = ansi * N * N + ansi * N + ansi;
  vector<int> path;
  while (E != S) {
    path.push_back(E);
    E = from[E];
  }
  path.push_back(S);
  reverse(path.begin(), path.end());

  vector<int> P[3];
  for (int p : path) {
    P[0].push_back(p / (N * N));
    P[1].push_back((p / N) % N);
    P[2].push_back(p % N);
  }
  for (auto& p : P) {
    for (int u : p) cout << u + 1 << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
