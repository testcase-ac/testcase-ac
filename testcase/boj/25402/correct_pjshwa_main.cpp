#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 250'000;
vector<int> graph[MAX + 1];
int parent[MAX + 1], usz[MAX + 1], anc[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

void dfs(int v, int p) {
  anc[v] = p;
  for (int u : graph[v]) {
    if (u == p) continue;
    dfs(u, v);
  }
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dfs(1, -1);

  for (int i = 1; i <= N; i++) parent[i] = i, usz[i] = 1;

  int Q;
  cin >> Q;
  while (Q--) {
    set<int> S;
    int K, x;
    cin >> K;
    while (K--) cin >> x, S.insert(x);

    for (int x : S) {
      if (S.count(anc[x])) Union(x, anc[x]);
    }

    set<int> groups;
    for (int x : S) groups.insert(Find(x));

    ll ans = 0;
    for (int g : groups) ans += (ll)usz[g] * (usz[g] - 1) / 2;

    cout << ans << '\n';

    // rollback
    for (int x : S) {
      parent[x] = x;
      usz[x] = 1;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
