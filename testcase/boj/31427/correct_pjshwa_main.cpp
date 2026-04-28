#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e4;
int parent[MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N, M, Q; cin >> N >> M >> Q;

  vector<tuple<int, int, int>> E;
  while (M--) {
    int u, v; string t; cin >> u >> v >> t;
    E.emplace_back(t[0] - 'A', u, v);
  }

  int P[5]; iota(P, P + 5, 0);
  vector<vector<int>> C;
  do {
    sort(E.begin(), E.end(), [&](auto& a, auto& b) {
      int aw = P[get<0>(a)], bw = P[get<0>(b)];
      return aw < bw;
    });
    iota(parent, parent + N + 1, 0);

    vector<int> Wc(5);
    for (auto& [t, u, v] : E) {
      if (Find(u) == Find(v)) continue;
      Union(u, v); ++Wc[t];
    }
    C.push_back(Wc);

  } while (next_permutation(P, P + 5));

  while (Q--) {
    ll U[5];
    for (int i = 0; i < 5; ++i) cin >> U[i];

    ll ans = 1e18;
    for (auto& Wc : C) {
      ll cost = 0;
      for (int i = 0; i < 5; ++i) cost += Wc[i] * U[i];
      ans = min(ans, cost);
    }
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
