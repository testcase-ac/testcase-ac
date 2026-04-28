#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
const ll INF = 1e18;
vector<pll> graph[MAX + 1];
ll cdist[MAX + 1];

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int N, M, J, K;
  cin >> N >> M >> J >> K;
  vector<int> A(K), B(K);
  for (int i = 0; i < K; i++) cin >> A[i];
  for (int i = 0; i < K; i++) cin >> B[i];
  while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }

  dijk(J);
  ll adist = INF, bdist = INF;
  for (int i = 0; i < K; i++) {
    adist = min(adist, cdist[A[i]]);
    bdist = min(bdist, cdist[B[i]]);
  }

  if (adist == INF && bdist == INF) cout << "-1\n";
  else if (adist <= bdist) cout << "A\n" << adist << '\n';
  else cout << "B\n" << bdist << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
