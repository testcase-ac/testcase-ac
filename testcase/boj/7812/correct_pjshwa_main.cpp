#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
vector<pii> graph[MAX];
ll ssz[MAX], ans[MAX];
int n;

ll dfs1(int v, int p) {
  ssz[v] = 1;
  ll res = 0;
  for (auto& [u, w] : graph[v]) {
    if (u == p) continue;

    res += dfs1(u, v) + w * ssz[u];
    ssz[v] += ssz[u];
  }
  return res;
}

void dfs2(int v, int p) {
  for (auto& [u, w] : graph[v]) {
    if (u == p) continue;

    ans[u] = ans[v] + (n - 2 * ssz[u]) * w;
    dfs2(u, v);
  }
}

void solve() {
  for (int i = 0; i < n; i++) graph[i].clear();
  memset(ssz, 0, sizeof ssz);

  for (int i = 0; i < n - 1; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    graph[a].push_back({b, w});
    graph[b].push_back({a, w});
  }
  ans[0] = dfs1(0, -1);
  dfs2(0, -1);
  cout << *min_element(ans, ans + n) << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n;
    if (n == 0) break;
    solve();
  }
}
