#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];
pair<int, int> gdur[MAX + 1][MAX + 1];

int gbonus(int ui, int vi, int wi) {
  if (gdur[ui][vi].first > wi || wi > gdur[ui][vi].second) return 0;
  return gdur[ui][vi].second - wi;
}

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
      di += gbonus(ui, vi, wi);
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int main() {
  fast_io();

  int n, m, a, b, k, g;
  cin >> n >> m >> a >> b >> k >> g;

  vector<int> groute(g);
  for (int i = 0; i < g; ++i) cin >> groute[i];

  while (m--) {
    int ui, vi, wi;
    cin >> ui >> vi >> wi;
    graph[ui].push_back({vi, wi});
    graph[vi].push_back({ui, wi});
  }

  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
    gdur[i][j] = {-1, -1};
  }

  int lt = -k;
  for (int i = 0; i < g - 1; i++) {
    int s = groute[i], t = groute[i + 1];
    for (auto& p : graph[s]) {
      if (p.first == t) {
        gdur[s][t] = gdur[t][s] = {lt, lt + p.second};
        lt += p.second;
        break;
      }
    }
  }

  dijk(a);
  cout << cdist[b] << '\n';
}
