#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  for (int i = 1, x; i <= n; i++) {
    cin >> cdist[i];
    pq.push({cdist[i], i});
  }
  while (m--) {
    int ai, xi, yi;
    cin >> ai >> xi >> yi;
    graph[xi].push_back({ai, yi});
    graph[yi].push_back({ai, xi});
  }

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto [v, t] : graph[ui]) {
      if (cdist[v] > cdist[t] + wi) {
        cdist[v] = cdist[t] + wi;
        pq.push({cdist[v], v});
      }
    }
  }

  cout << cdist[1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
