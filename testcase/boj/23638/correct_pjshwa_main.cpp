#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
vector<int> graph[MAX + 1];
int ginv[MAX + 1], t[MAX + 1], depth[MAX + 1], diamv[MAX + 1];
bool vis[MAX + 1], is_cycle[MAX + 1], marked[MAX + 1];
int cdepth;

pii maxd(int v, int cd) {
  vis[v] = true;
  int mv = v, md = cd;
  for (int d : graph[v]) {
    if (!vis[d] && (!is_cycle[d] || marked[d])) {
      auto [dv, dd] = maxd(d, cd + 1);
      if (md < dd) {
        md = dd;
        mv = dv;
      }
    }
  }
  return {mv, md};
}

void dfs(int v, int par) {
  vis[v] = 1;
  for (int d : graph[v]) {
    if (!vis[d]) ginv[d] = v, dfs(d, v);
    else if (par != d && !is_cycle[d]) {
      // Cycle is detected
      for (int x = v; x != d; x = ginv[x]) is_cycle[x] = 1;
      is_cycle[d] = 1;
    }
  }
}

void ddfs(int v, int dpt) {
  vis[v] = 1;
  cdepth = max(cdepth, dpt);
  for (int d : graph[v]) {
    if (!vis[d] && !is_cycle[d]) ddfs(d, dpt + 1);
  }
}

vector<int> ccs;
void cdfs(int v) {
  vis[v] = 1;
  ccs.push_back(depth[v]);
  for (int d : graph[v]) {
    if (!vis[d] && is_cycle[d]) cdfs(d);
  }
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  dfs(1, -1);

  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; i++) {
    if (is_cycle[i]) {
      cdepth = 0;
      ddfs(i, 0);
      depth[i] = cdepth;
    }
  }

  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; i++) {
    if (is_cycle[i]) {
      cdfs(i);
      break;
    }
  }

  int ans = 0;
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; i++) {
    if (is_cycle[i]) {
      marked[i] = true;
      auto [mv, md] = maxd(i, 0);
      diamv[i] = mv;
      marked[i] = false;
    }
  }
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; i++) {
    if (is_cycle[i]) {
      marked[i] = true;
      auto [mv, md] = maxd(diamv[i], 0);
      ans = max(ans, md);
      marked[i] = false;
    }
  }

  priority_queue<pii> pq;
  int csz = ccs.size();
  for (int i = 0; i < csz; i++) pq.push({ccs[i] + csz - i, i});

  int bonus = 0;
  for (int i = 0; i < csz; i++) {
    while (pq.top().second <= i) pq.pop();
    if (i > 0) pq.push({ccs[i - 1] + 1 - bonus, csz});
    ans = max(ans, pq.top().first + ccs[i] + bonus);
    bonus++;
  }

  cout << csz << ' ' << ans << '\n';
}
