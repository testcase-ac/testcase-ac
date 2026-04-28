#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  vector<int> A; int x;
  while (cin >> x) {
    if (x == 0) break;
    A.push_back(x);
  }
  int N = A.size();

  vector<int> adj[N + 1], S, deg(N + 1);
  auto add_edge = [&](int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    --deg[u], --deg[v];
  };

  int u = 0;
  for (int& x : A) {
    if (x > 0) {
      deg[++u] = x;
      if (!S.empty()) add_edge(u, S.back());
      S.push_back(u);
    }
    else {
      int z = S.size();
      add_edge(S[z - 1 + x], S[z - 1]);
    }

    while (!S.empty() && deg[S.back()] == 0) S.pop_back();
  }
  assert(S.empty());

  for (int i = 1; i <= u; ++i) {
    sort(adj[i].begin(), adj[i].end());

    cout << i << ' ';
    for (int v : adj[i]) cout << v << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
