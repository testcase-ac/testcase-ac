#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}
 
const ll MAXN = 2e5, INF = 1e18;
vector<pii> adj_a[MAXN + 1], adj_b[MAXN + 1];
ll cdist[MAXN + 1];
 
void solve() {
  int N, K, X, Y; cin >> N >> K >> X >> Y;
  while (X--) {
    int s, e, d; cin >> s >> e >> d;
    adj_a[s].emplace_back(e, d);
    adj_a[e].emplace_back(s, d);
  }
  while (Y--) {
    int s, e, d; cin >> s >> e >> d;
    adj_b[s].emplace_back(e, d);
    adj_b[e].emplace_back(s, d);
  }
 
  using T = pair<ll, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  fill(cdist, cdist + N + 1, INF);
  pq.emplace(0, 1); cdist[1] = 0;
 
  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (cdist[u] < d) continue;
 
    for (auto [v, w] : adj_a[u]) {
      if (cdist[v] > cdist[u] + w) {
        cdist[v] = cdist[u] + w;
        pq.emplace(cdist[v], v);
      }
    }
    for (auto [v, w] : adj_b[u]) {
      ll wait = max(0LL, K - d);
      if (cdist[v] > cdist[u] + w + wait) {
        cdist[v] = cdist[u] + w + wait;
        pq.emplace(cdist[v], v);
      }
    }
  }
 
  cout << cdist[N] << '\n';
}
 
int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
