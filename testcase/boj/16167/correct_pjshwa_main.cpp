#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
pii cdist[MAX + 1];
vector<pii> adj[MAX + 1];

void solve() {
  int N, R; cin >> N >> R;
  for (int i = 1; i <= N; i++) cdist[i] = {INF, INF};

  while (R--) {
    int a, b, c, d, e; cin >> a >> b >> c >> d >> e;

    int cost = e <= 10 ? c : c + d * (e - 10);
    adj[a].emplace_back(b, cost);
  }

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.emplace(0, 1, 1); cdist[1] = {0, 1};
  while (!pq.empty()) {
    auto [dist, cnt, u] = pq.top(); pq.pop();
    if (cdist[u] < pii(dist, cnt)) continue;

    for (auto [v, cost] : adj[u]) {
      int ndist = dist + cost;
      if (cdist[v].first > ndist || (cdist[v].first == ndist && cdist[v].second > cnt + 1)) {
        cdist[v] = {ndist, cnt + 1};
        pq.emplace(ndist, cnt + 1, v);
      }
    }
  }

  if (cdist[N].first == INF) cout << "It is not a great way.\n";
  else cout << cdist[N].first << ' ' << cdist[N].second << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
