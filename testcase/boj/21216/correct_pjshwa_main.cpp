#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  queue<pii> q;
  q.push({1, 0});
  vis[1] = true;

  int ld = 0;
  while (!q.empty()) {
    auto [node, depth] = q.front();
    q.pop();

    if (depth > ld) {
      ld = depth;
    }

    for (int el : graph[node]) {
      if (!vis[el]) {
        vis[el] = true;
        q.push({el, depth + 1});
      }
    }

  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) return cout << "-1\n", void();
  }

  cout << ceil(log2(ld)) + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
