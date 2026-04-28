#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
vector<int> graph[MAX + 1];
int sz[MAX + 1];

void dfs1(int v, int p) {
  sz[v] = 1;
  for (int u : graph[v]) {
    if (u == p) continue;
    dfs1(u, v);
    sz[v] += sz[u];
  }
}

void solve() {
  int N;
  cin >> N;

  vector<int> factors;
  for (int i = 1; i < N; i++) {
    if (N % i == 0) factors.push_back(i);
  }

  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  vector<int> ans;
  dfs1(1, 0);

  for (int f : factors) {
    int E = 0;
    for (int i = 2; i <= N; i++) {
      if (sz[i] % f == 0) E++;
    }
    if (E == N / f - 1) ans.push_back(E);
  }

  sort(ans.begin(), ans.end());
  for (int e : ans) cout << e << " ";
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
