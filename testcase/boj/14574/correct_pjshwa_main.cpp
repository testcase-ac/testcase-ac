#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e3, INF = 1e9 + 7;
int p[MAX], c[MAX];
int mreach[MAX], from[MAX];
vector<int> graph[MAX];
vector<pii> edges;
bool used[MAX], vis[MAX];

int dist(int i, int j) {
  return (c[i] + c[j]) / abs(p[i] - p[j]);
}

void dfs(int v, int p) {
  vis[v] = true;
  for (int i : graph[v]) {
    if (!vis[i]) dfs(i, v);
  }
  if (p != -1) edges.push_back({p, v});
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> p[i] >> c[i];
  fill(mreach, mreach + n, INF);
  memset(from, -1, sizeof from);

  // Modified Prim's algorithm
  ll ans = 0;
  mreach[0] = 0;

  for (int i = 0; i < n; i++) {
    int wgt = INF;
    int sv = -1;
    for (int j = 0; j < n; j++) { 
      if (used[j]) continue;
      if (mreach[j] < wgt) sv = j, wgt = mreach[j];
    }

    used[sv] = true;
    if (from[sv] != -1) {
      graph[sv].push_back(from[sv]);
      graph[from[sv]].push_back(sv);
    }
    ans -= wgt;

    for (int to = 0; to < n; to++) {
      if (sv == to) continue;
      int d = -dist(sv, to);
      if (d < mreach[to]) {
        mreach[to] = d;
        from[to] = sv;
      }
    }
  }

  cout << ans << '\n';

  dfs(0, -1);
  for (auto e : edges) cout << e.first + 1 << ' ' << e.second + 1 << '\n';
}
