#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4e5;
int parent[MAX + 1], S[MAX + 1];

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
  int N, M, K;
  cin >> N >> M >> K;

  vector<pii> E(M);
  for (int i = 0; i < M; i++) {
    int U, V;
    cin >> U >> V;
    E[i] = {U, V};
  }

  for (int i = 1; i <= N; i++) cin >> S[i];
  for (int i = 1; i <= N; i++) parent[i] = i;
  for (auto& [U, V] : E) {
    if (S[U] == S[V]) Union(U, V);
  }

  map<pii, vector<pii>> e2x;
  for (auto [U, V] : E) {
    U = Find(U);
    V = Find(V);

    int u[2] = {S[U], S[V]};
    sort(u, u + 2);

    e2x[{u[0], u[1]}].push_back({U, V});
  }

  int Q;
  cin >> Q;
  map<pii, vector<tii>> q2x;
  for (int i = 0; i < Q; i++) {
    int A, B;
    cin >> A >> B;

    A = Find(A);
    B = Find(B);

    int u[2] = {S[A], S[B]};
    sort(u, u + 2);

    q2x[{u[0], u[1]}].push_back({A, B, i});
  }

  vector<int> ppar(N + 1), ans(Q);
  for (int i = 1; i <= N; i++) ppar[i] = parent[i];

  for (auto& [G, qs] : q2x) {
    auto& edges = e2x[G];
    for (auto& [U, V] : edges) Union(U, V);
    for (auto& [A, B, i] : qs) ans[i] = Find(A) == Find(B);
    for (auto& [U, V] : edges) {
      parent[U] = ppar[U];
      parent[V] = ppar[V];
    }
  }

  for (int e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
