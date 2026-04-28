#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
int A[MAX + 1], parent[MAX + 1];
vector<int> adj[MAX + 1];

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

  if (x != y) parent[y] = x;
}

void solve() {
  int N; cin >> N;

  map<int, vector<int>> by_weight;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    by_weight[-A[i]].push_back(i);
  }

  iota(parent + 1, parent + N + 1, 1);
  for (int i = 0; i < N - 1; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  ll lwgt = INF, use = 0, ans = 0;
  for (auto [w, vv] : by_weight) {
    int wgt = -w;
    ans += use * (lwgt - wgt);

    for (int v : vv) {
      use++;
      for (int u : adj[v]) {
        if (Find(u) == Find(v)) continue;
        if (A[u] < A[v]) continue;
        Union(u, v); use--;
      }
    }
    lwgt = wgt;
  }
  ans += use * lwgt;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
