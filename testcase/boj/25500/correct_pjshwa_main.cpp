#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tii = tuple<int, int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
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
  int N, K;
  cin >> N >> K;
  vector<tii> cities(N);
  for (int i = 0; i < N; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    cities[i] = {x, y, z, i};
  }

  sort(cities.begin(), cities.end(), [] (const tii &a, const tii &b) {
    auto [ax, ay, az, ai] = a;
    auto [bx, by, bz, bi] = b;
    return ax < bx;
  });
  for (int i = 0; i < N - 1; i++) {
    auto [ax, ay, az, ai] = cities[i];
    auto [bx, by, bz, bi] = cities[i + 1];

    int d = min(abs(ax - bx), abs(ay - by));
    graph[ai].push_back({bi, d});
    graph[bi].push_back({ai, d});
  }

  sort(cities.begin(), cities.end(), [] (const tii &a, const tii &b) {
    auto [ax, ay, az, ai] = a;
    auto [bx, by, bz, bi] = b;
    return ay < by;
  });
  for (int i = 0; i < N - 1; i++) {
    auto [ax, ay, az, ai] = cities[i];
    auto [bx, by, bz, bi] = cities[i + 1];

    int d = min(abs(ax - bx), abs(ay - by));
    graph[ai].push_back({bi, d});
    graph[bi].push_back({ai, d});
  }

  for (int i = 0; i < N; i++) {
    auto [ax, ay, az, ai] = cities[i];

    int rem = az % K;
    if (rem == 0) {
      graph[ai].push_back({N, az});
      graph[N].push_back({ai, az});
    }
    else {
      graph[ai].push_back({N + rem, az});
      graph[N + K - rem].push_back({ai, az});
    }
  }

  dijk(0);
  for (int i = 0; i < N; i++) cout << cdist[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
