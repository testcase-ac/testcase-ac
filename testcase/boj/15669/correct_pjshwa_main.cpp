#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
int level[MAX + 1], ec[MAX + 1], oc[MAX + 1];

void dfs(int v, int p, int o) {
  level[v] = o;
  if (o & 1) oc[v]++;
  else ec[v]++;

  for (int u : graph[v]) {
    if (u == p) continue;
    dfs(u, v, o + 1);
    ec[v] += ec[u];
    oc[v] += oc[u];
  }
}

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dfs(1, -1, 0);

  while (q--) {
    int u, v, c;
    cin >> u >> v >> c;
    if (level[u] > level[v]) swap(u, v);

    int uoc = oc[1] - oc[v], uec = ec[1] - ec[v];
    int voc = oc[v], vec = ec[v];

    ll ue, uo, ve, vo;
    if (level[u] & 1) ue = uoc, uo = uec, ve = vec, vo = voc;
    else ue = uec, uo = uoc, ve = voc, vo = vec;

    ll res;
    if (c) res = ue * ve + uo * vo;
    else res = ue * vo + uo * ve;

    cout << res << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
