#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int A[MAX + 1], parent[MAX + 1], usz[MAX + 1];
vector<pii> by_prime[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x); y = Find(y);
  if (x == y) return;
  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  int N; cin >> N;

  int ans = 0;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    if (A[i] > 1) ans = 1;
  }

  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    int g = __gcd(A[u], A[v]);

    int og = g;
    for (int p = 2; p * p <= og; ++p) {
      if (g % p == 0) {
        by_prime[p].emplace_back(u, v);
        while (g % p == 0) g /= p;
      }
    }
    if (g > 1) by_prime[g].emplace_back(u, v);
  }

  iota(parent, parent + N + 1, 0);
  fill(usz, usz + N + 1, 1);

  for (int p = 2; p <= MAX; ++p) {
    if (by_prime[p].empty()) continue;

    vector<int> used;
    for (auto [u, v] : by_prime[p]) {
      used.push_back(u); used.push_back(v);
      Union(u, v); ans = max(ans, usz[Find(u)]);
    }

    for (int u : used) {
      parent[u] = u;
      usz[u] = 1;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
