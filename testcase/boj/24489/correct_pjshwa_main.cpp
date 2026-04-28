#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int parent[MAX + 1], usz[MAX + 1], ans[MAX + 1];
vector<int> adj[MAX + 1];

void dfs(int v, int x) {
  ans[v] = x;
  for (int u : adj[v]) {
    if (ans[u] == -1) dfs(u, x);
  }
}

void solve() {
  int N, Q; cin >> N >> Q;

  vector<tuple<string, int, int, int>> queries;
  map<int, pii> adds;

  set<int> perm;
  for (int i = 1; i <= N; i++) perm.insert(i);

  int it = 0;
  for (int i = 1; i <= Q; i++) {
    string op; cin >> op;
    if (op == "A") {
      int x, y; cin >> x >> y;
      adds[++it] = {x, y};
    }
    if (op == "D") {
      int x; cin >> x;
      queries.push_back({"D", x, 0, i});
      perm.erase(x);
    }
    if (op == "R") {
      int e; cin >> e;
      auto [x, y] = adds[e];
      adds.erase(e);
      queries.push_back({"R", x, y, i});
    }
  }

  for (auto [_, p] : adds) {
    auto [x, y] = p;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  memset(ans, -1, sizeof(ans));
  for (int x : perm) {
    if (ans[x] == -1) dfs(x, Q);
  }

  reverse(queries.begin(), queries.end());
  for (auto [op, x, y, i] : queries) {
    if (op == "D") {
      if (ans[x] == -1) dfs(x, i - 1);
    }
    if (op == "R") {
      adj[x].push_back(y);
      adj[y].push_back(x);
      if (ans[x] == -1 && ans[y] == -1) continue;

      if (ans[x] == -1) dfs(x, i - 1);
      if (ans[y] == -1) dfs(y, i - 1);
    }
  }

  for (int i = 1; i <= N; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
