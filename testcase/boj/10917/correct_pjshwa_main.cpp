#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int cdist[MAX + 1];
vector<int> graph[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
  }

  memset(cdist, -1, sizeof(cdist));
  queue<pii> q;
  q.push({1, 0});
  cdist[1] = 0;

  while (!q.empty()) {
    auto [u, d] = q.front();
    q.pop();
    for (auto v : graph[u]) {
      if (cdist[v] == -1 || cdist[v] > d + 1) {
        cdist[v] = d + 1;
        q.push({v, d + 1});
      }
    }
  }

  cout << cdist[n] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
