#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<pii> graph[100001];
bool vis[100001];
pii maxd(int node, int cd) {
  vis[node] = true;

  int mv = node, md = cd, dv, dd;
  for (auto[v, d] : graph[node]) {
    if (!vis[v]) {
      auto[dv, dd] = maxd(v, cd + d);
      if (md < dd) {
        md = dd;
        mv = dv;
      }
    }
  }

  return {mv, md};
}

int main() {
  fast_io();

  int n, v, k, d;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> v;
    while (1) {
      cin >> k;
      if (k == -1) break;
      cin >> d;

      graph[v].push_back({k, d});
    }
  }

  auto[mv, md] = maxd(1, 0);

  memset(vis, 0, sizeof(vis));
  tie(mv, md) = maxd(mv, 0);
  cout << md << '\n';
}
