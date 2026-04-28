#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<tii> edges;
int N, M, C;

const ll INF = 1e18;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];

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
  cin >> N >> M >> C;

  edges.resize(M);
  for (int i = 0; i < M; i++) {
    int ai, bi, di;
    cin >> ai >> bi >> di;
    edges[i] = {ai, bi, di};

    graph[ai].push_back({bi, di});
    graph[bi].push_back({ai, di});
  }

  dijk(1);
  map<ll, vector<int>> dinv;
  for (auto& [ai, bi, di] : edges) dinv[max(cdist[ai], cdist[bi])].push_back(di);

  ll ans = 0;
  for (auto& [ai, bi, di] : edges) ans += di;

  ll cd = ans;
  for (auto& [l, dv] : dinv) {
    for (ll d : dv) cd -= d;
    ans = min(ans, cd + l * C);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
