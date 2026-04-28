#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pld = pair<long double, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200;
const ll INF = 1e18;
tii u[MAX];
vector<pld> graph[MAX];
long double cdist[MAX];
int from[MAX];

void dijk(int s) {
  fill(cdist, cdist + MAX, INF);
  memset(from, -1, sizeof(from));
  cdist[s] = 0;

  priority_queue<pld, vector<pld>, greater<pld>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [di, vi] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        from[vi] = ui;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    int f, x, y;
    cin >> f >> x >> y;
    u[i] = {f, x, y};
  }
  while (m--) {
    int a, b;
    string op;
    cin >> a >> b >> op;
    auto [af, ax, ay] = u[a];
    auto [bf, bx, by] = u[b];
    int fdiff = abs(af - bf) * 5;
    long double dist = sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by) + fdiff * fdiff);

    if (op == "walking" || op == "stairs") {
      graph[a].push_back({dist, b});
      graph[b].push_back({dist, a});
    }
    if (op == "escalator") {
      graph[a].push_back({1, b});
      graph[b].push_back({3 * dist, a});
    }
    if (op == "lift") {
      graph[a].push_back({1, b});
      graph[b].push_back({1, a});
    }
  }

  int q;
  cin >> q;
  vector<tii> queries;
  for (int i = 0; i < q; i++) {
    int a, b;
    cin >> a >> b;
    queries.push_back({a, b, i});
  }
  sort(queries.begin(), queries.end());

  vector<vector<int>> ans(q);
  int last = -1;
  for (auto [a, b, i] : queries) {
    if (last != a) dijk(a);
    vector<int> traj;

    while (b != -1) {
      traj.push_back(b);
      b = from[b];
    }

    reverse(traj.begin(), traj.end());
    ans[i] = traj;
    last = a;
  }

  for (auto& v : ans) {
    for (auto& e : v) cout << e << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
