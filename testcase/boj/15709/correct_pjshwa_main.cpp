#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 30000;
const ll INF = 1e18;
ll cdist[101][MAX + 1];
vector<pll> graph[MAX + 1];
int n;

void dijk(int b, int s) {
  for (int i = 1; i <= n; ++i) cdist[b][i] = INF;
  cdist[b][s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[b][ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      if (cdist[b][vi] > di + wi) {
        cdist[b][vi] = di + wi;
        pq.push({cdist[b][vi], vi});
      }
    }
  }
}

int main() {
  fast_io();

  int h, m, b, k, q;
  cin >> h >> m >> b >> k >> q;
  n = h + m + b;

  while (k--) {
    int ui, vi, wi;
    cin >> ui >> vi >> wi;
    graph[ui].push_back({vi, wi});
    graph[vi].push_back({ui, wi});
  }

  for (int i = h + m + 1; i <= n; ++i) dijk(i - h - m, i);

  while (q--) {
    int s, e;
    cin >> s >> e;

    ll ans = INF;
    for (int i = h + m + 1; i <= n; ++i) {
      ans = min(ans, cdist[i - h - m][s] + cdist[i - h - m][e]);
    }

    if (ans == INF) cout << "-1\n";
    else cout << ans << '\n';
  }
}
