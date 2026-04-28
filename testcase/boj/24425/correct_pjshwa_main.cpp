#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5, MAXB = 31, INF = 0x3f3f3f3f;
vector<pii> graph[MAX + 1];
int cdist[MAXB][MAX + 1];

void dijk(int s) {
  for (int b = 0; b < MAXB; b++) {
    fill(cdist[b], cdist[b] + MAX + 1, INF);
  }
  cdist[0][s] = 0;

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.push({0, 0, s});

  while (!pq.empty()) {
    auto [w, b, u] = pq.top(); pq.pop();

    if (w > cdist[b][u]) continue;

    for (auto& [v, c] : graph[u]) {
      if (c == 1) {
        if (cdist[b][v] > w + (1 << b)) {
          cdist[b][v] = w + (1 << b);
          pq.push({w + (1 << b), b, v});
        }
      }
      if (c == 2) {
        if (b + 1 < MAXB && cdist[b + 1][v] > w) {
          cdist[b + 1][v] = w;
          pq.push({w, b + 1, v});
        }
      }
    }
  }
}

void solve() {
  int N, M, Q, L;
  cin >> N >> M >> Q >> L;
  while (M--) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].emplace_back(b, c);
    graph[b].emplace_back(a, c);
  }

  dijk(1);
  while (Q--) {
    ll v, ans = INF;
    cin >> v;

    ll g = 1;
    for (int b = 0; b < MAXB; b++) {
      if (g + cdist[b][v] <= L) ans = min(ans, g + cdist[b][v]);
      g *= 2;
    }

    if (ans == INF) cout << "Large\n";
    else cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
