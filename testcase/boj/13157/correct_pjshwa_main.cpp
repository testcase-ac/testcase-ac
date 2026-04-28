#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];

void solve() {
  int n, fval;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int m, t;
    cin >> m >> t;
    if (i == n - 1) fval = t;

    while (m--) {
      int s, x;
      cin >> s >> x;
      set<int> avoid;
      while (s--) {
        int si;
        cin >> si;
        avoid.insert(si - 1);
      }
      x--;
      for (int j = 0; j < n; j++) {
        int c = i * n + j;
        if (!avoid.count(j)) graph[c].push_back({x * n + i, t});
      }
    }
  }

  fill(cdist, cdist + MAX + 1, INF);
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  for (int s = 0; s < n; s++) {
    cdist[s] = 0;
    pq.push({0, s});
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

  ll ans = INF;
  for (int i = 0; i < n; i++) ans = min(ans, cdist[(n - 1) * n + i]);

  if (ans == INF) cout << "impossible\n";
  else cout << ans + fval << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
