#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5 + 10;
const ll INF = 1e18;
ll cdist[2 * MAX + 5];
tuple<int, int, int> pts[2 * MAX + 5];
vector<pll> graph[2 * MAX + 5];

void dijk(int s) {
  fill(cdist, cdist + 2 * MAX + 5, INF);
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
  int n, xl, yl, xb, yb;
  cin >> n >> xl >> yl >> xb >> yb;

  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    pts[i] = {x, y, i};
  }
  pts[n] = {xl, yl, n};
  pts[n + 1] = {xb, yb, n + 1};
  int si = n, ei = n + 1;
  n += 2;

  for (int i = 0; i < n; i++) {
    graph[i].push_back({i + MAX, 1});
    graph[i + MAX].push_back({i, 1});
  }

  sort(pts, pts + n, [] (auto &a, auto &b) {
    return get<0>(a) < get<0>(b);
  });
  for (int i = 0; i < n - 1; i++) {
    auto [xp, yp, ip] = pts[i];
    auto [xq, yq, iq] = pts[i + 1];
    if (xp == xq) {
      graph[ip].push_back({iq, 0});
      graph[iq].push_back({ip, 0});
    }
  }

  sort(pts, pts + n, [] (auto &a, auto &b) {
    return get<1>(a) < get<1>(b);
  });
  for (int i = 0; i < n - 1; i++) {
    auto [xp, yp, ip] = pts[i];
    auto [xq, yq, iq] = pts[i + 1];
    if (yp == yq) {
      graph[ip + MAX].push_back({iq + MAX, 0});
      graph[iq + MAX].push_back({ip + MAX, 0});
    }
  }

  ll ans = INF;
  dijk(si);
  ans = min({ans, cdist[ei], cdist[ei + MAX]});
  dijk(si + MAX);
  ans = min({ans, cdist[ei], cdist[ei + MAX]});

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
