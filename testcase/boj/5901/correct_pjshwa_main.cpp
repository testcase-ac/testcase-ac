#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll INF = 1e18;
const int MAX = 1e4;
ll cdist[5][MAX + 1];
vector<pll> graph[MAX + 1];

void dijk(int d, int s) {
  cdist[d][s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[d][ui]) continue;

    for (auto &p : graph[ui]) {
      auto[di, vi] = p;
      if (cdist[d][vi] > di + wi) {
        cdist[d][vi] = di + wi;
        pq.push({cdist[d][vi], vi});
      }
    }
  }
}

int main() {
  fast_io();

  int n, m, k;
  cin >> n >> m >> k;
  vector<int> markets(k);
  for (int i = 0; i < k; i++) cin >> markets[i];

  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({w, v});
    graph[v].push_back({w, u});
  }

  for (int i = 0; i < k; i++) fill(cdist[i], cdist[i] + n + 1, INF);
  for (int i = 0; i < k; i++) dijk(i, markets[i]);

  ll ans = INF;
  for (int i = 1; i <= n; i++) {
    bool eligible = true;
    for (int j = 0; j < k; j++) eligible &= i != markets[j];
    if (!eligible) continue;

    int p[k];
    for (int j = 0; j < k; j++) p[j] = j;

    do {
      ll cur = cdist[p[0]][i] + cdist[p[k - 1]][i];
      for (int j = 0; j < k - 1; j++) cur += cdist[p[j]][markets[p[j + 1]]];
      ans = min(ans, cur);
    } while (next_permutation(p, p + k));
  }

  cout << ans << '\n';
}
