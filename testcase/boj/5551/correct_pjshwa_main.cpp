#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const int MAX = 3000;
const ll INF = 1e14;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];
vector<int> malls;

void dijk() {
  fill(cdist, cdist + MAX + 1, INF);

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  for (int& mi : malls) {
    cdist[mi] = 0;
    pq.push({0, mi});
  }

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

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m, k;
  cin >> n >> m >> k;
  while (m--) {
    int a, b, w;
    cin >> a >> b >> w;
    graph[a].push_back({b, w});
    graph[b].push_back({a, w});
  }
  malls.resize(k);
  for (int i = 0; i < k; i++) cin >> malls[i];

  dijk();

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, cdist[i]);

    for (auto &p : graph[i]) {
      auto [vi, di] = p;
      ll diff = max(cdist[vi], cdist[i]) - min(cdist[vi], cdist[i]);
      if (diff >= di) continue;
      di -= diff;
      ans = max(ans, max(cdist[vi], cdist[i]) + (di + 1) / 2);
    }
  }
  cout << ans << '\n';
}
