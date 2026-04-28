#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, MOD = 1e6 + 3;
int D[MAX], V[MAX];
int parent[MAX];
ll fac[MAX + 1], ifac[MAX + 1];

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

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

void quit() {
  cout << "0\n";
  exit(0);
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

  int Vx = V[x], Vy = V[y];
  if (Vx != Vy) {
    if (Vx == -1) V[x] = Vy;
    else if (Vy == -1) V[y] = Vx;
    else quit();
  }
  parent[y] = x;
}

void solve() {
  int N, K; cin >> N >> K;

  memset(V, -1, sizeof(V));
  iota(parent, parent + N, 0);

  for (int i = 0; i < N - K + 1; i++) {
    cin >> D[i];
    if (i == 0) continue;

    int dif = D[i] - D[i - 1];
    if (abs(dif) > 1) quit();

    int u = Find(i - 1), v = Find(i - 1 + K);
    if (dif == 1) {
      if (V[u] == 1 || V[v] == 0) quit();
      V[u] = 0; V[v] = 1;
    }
    else if (dif == 0) Union(u, v);
    else {
      if (V[u] == 0 || V[v] == 1) quit();
      V[u] = 1; V[v] = 0;
    }
  }

  int G = 0;
  for (int i = 0; i < K; i++) {
    int v = Find(i);
    if (V[v] == 1) D[0]--;
    if (V[v] == -1) G++;
  }
  cout << C(G, D[0]) << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX] = lpow(fac[MAX], MOD - 2, MOD);
  for (int i = MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
