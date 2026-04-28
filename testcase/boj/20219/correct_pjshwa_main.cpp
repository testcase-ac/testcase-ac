#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
bool vis[MAX + 1], group[MAX + 1];
vector<int> graph[MAX + 1];
int gs;

void dfs(int v, bool g) {
  vis[v] = 1, group[v] = g, gs += g;
  for (int d : graph[v]) if (!vis[d]) dfs(d, !g);
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i, 1);
  }

  if (n % 2 == 0 && (gs & 1)) {
    bool able = false;
    for (int i = 1; i <= n; i++) {
      if (group[i] && graph[i].size() < n - gs) {
        able = true;
        break;
      }
    }

    if (able) cout << n / 2 << '\n';
    else cout << n / 2 - 1 << '\n';
  }
  else cout << n / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
