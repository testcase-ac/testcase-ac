#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];
int banp;

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
      if (vi == banp) continue;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int main() {
  fast_io();

  int v, e;
  cin >> v >> e;

  while (e--) {
    int ui, vi, wi;
    cin >> ui >> vi >> wi;
    graph[ui].push_back({vi, wi});
  }

  int x, y, z;
  cin >> x >> y >> z;

  ll ans1, ans2;
  dijk(x);
  ans1 = cdist[y];
  dijk(y);
  ans1 += cdist[z];

  banp = y;
  dijk(x);
  ans2 = cdist[z];

  if (ans1 >= INF) cout << -1;
  else cout << ans1;
  cout << ' ';
  if (ans2 >= INF) cout << -1;
  else cout << ans2;
  cout << '\n';
}
