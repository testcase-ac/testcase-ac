#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
vector<int> adj[MAXN + 1];
int A[MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for (int i = 1; i <= N; ++i) {
    int V[5]{}, x = 1;
    for (int u : adj[i]) {
      if (A[u] == 0) continue;
      V[A[u]] = 1;
    }
    while (V[x]) ++x;
    assert(x <= 4);
    A[i] = x;
    cout << x;
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
