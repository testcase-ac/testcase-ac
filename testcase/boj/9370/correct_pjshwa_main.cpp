#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const int MAX = 2000;
const ll INF = 1e14;
ll sdist[MAX + 1], gdist[MAX + 1], hdist[MAX + 1];
vector<pll> graph[MAX + 1];

void dijk(ll* cdist, int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto[vi, di] = p;
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

void solve() {
  int n, m, t, s, g, h;
  cin >> n >> m >> t >> s >> g >> h;

  for (int i = 1; i <= n; i++) graph[i].clear();

  while (m--) {
    int a, b, d;
    cin >> a >> b >> d;
    graph[a].push_back({b, d});
    graph[b].push_back({a, d});
  }

  dijk(sdist, s);
  dijk(gdist, g);
  dijk(hdist, h);

  set<int> ans;
  while (t--) {
    int ep;
    cin >> ep;

    if (sdist[ep] == INF) continue;
    if (sdist[ep] == sdist[g] + gdist[h] + hdist[ep] || sdist[ep] == sdist[h] + hdist[g] + gdist[ep]) {
      ans.insert(ep);
    }
  }

  for (auto &i : ans) cout << i << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
