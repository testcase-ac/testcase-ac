#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, MAXV = 10000, INF = 0x3f3f3f3f;
vector<tii> graph[MAX + 1];
int cdist[MAX + 1][MAXV + 1], T;

void dijk(int s) {
  for (int i = 1; i <= MAX; i++) fill(cdist[i], cdist[i] + MAXV + 1, INF);
  cdist[s][0] = 0;

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.push({0, s, 0});

  while (!pq.empty()) {
    auto [w, v, t] = pq.top();
    pq.pop();

    if (w > cdist[v][t]) continue;
    for (auto& [u, at, am] : graph[v]) {
      if (at + t > T) continue;
      if (cdist[u][at + t] > w + am) {
        cdist[u][at + t] = w + am;
        pq.push({cdist[u][at + t], u, at + t});
      }
    }
  }
}

void solve() {
  int N, M, L;
  cin >> N >> T >> M >> L;
  while (L--) {
    int u, v, t, m;
    cin >> u >> v >> t >> m;
    graph[u].push_back({v, t, m});
    graph[v].push_back({u, t, m});
  }

  dijk(1);

  int ans = INF;
  for (int i = 0; i <= T; i++) ans = min(ans, cdist[N][i]);
  if (ans > M) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
