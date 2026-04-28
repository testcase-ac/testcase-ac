#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
vector<int> graph[MAX + 1];
int fruit[MAX + 1];
bool vis[MAX + 1];

pii maxd(int node, int cd) {
  vis[node] = true;

  int mv = node, md = cd, dv, dd;
  for (int v : graph[node]) {
    if (!vis[v]) {
      tie(dv, dd) = maxd(v, cd + fruit[v]);
      if (md < dd) {
        md = dd;
        mv = dv;
      }
      else if (md == dd && mv > dv) mv = dv;
    }
  }

  return {mv, md};
}

int main() {
  fast_io();

  int n, v, k;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> fruit[i];

  for (int i = 1; i <= n - 1; i++) {
    cin >> v >> k;
    graph[v].push_back(k);
    graph[k].push_back(v);
  }

  int mv, md, mnv = 2e9;

  tie(mv, md) = maxd(1, fruit[1]);
  mnv = min(mnv, mv);

  memset(vis, 0, sizeof(vis));

  tie(mv, md) = maxd(mv, fruit[mv]);
  mnv = min(mnv, mv);

  cout << md << ' ' << mnv;
}
