#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4;
int A[MAX + 1];
vector<int> adj[MAX + 1];
vector<pii> V[MAX + 1];

void dfs1(int v) {
  bool leaf = true;
  for (int u : adj[v]) {
    dfs1(u);
    leaf = false;
    for (a : V[u]) V[v].push_back(l + A[v]);
  }
  if (leaf) V[v].push_back(A[v]);
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    int Si; cin >> Si >> A[i];
    if (Si) adj[Si].push_back(i);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
