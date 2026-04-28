#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 7;
int parent[MAX + 1], usz[MAX + 1];
int n, m;

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

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

void solve() {
  if (m == 0) cout << lpow(2, n, MOD) << '\n';
  else {
    for (int i = 1; i <= n; i++) parent[i] = i, usz[i] = 1;
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      Union(u, v);
    }

    set<int> s;
    for (int i = 1; i <= n; i++) s.insert(Find(i));

    int ans = (lpow(2, s.size(), MOD) + 1) % MOD;
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    solve();
  }
}
