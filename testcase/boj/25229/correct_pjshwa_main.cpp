#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4, MAXV = 100, INF = 1e9 + 7;
int a[MAX + 1], d[MAX + 1][MAX + 1];
vector<int> graph[MAX + 1];

int lp[MAXV + 1];
vector<int> pr;

int lcm(int a, int b) {
  return a / __gcd(a, b) * b;
}

int r(int x, int val, int p) {
  if (d[x][val] != -1) return d[x][val];

  int scost = 0;
  for (int u : graph[x]) {
    if (u == p) continue;

    int ucost = INF;
    for (int p : pr) {
      int l = lcm(p, val);
      for (int j = l; j <= MAX; j += l) {
        ucost = min(ucost, r(u, p, x) + (a[u] == j ? 0 : j));
      }
    }
    scost += ucost;
  }

  return d[x][val] = scost;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  memset(d, -1, sizeof(d));
  int ans = INF;
  for (int p : pr) ans = min(ans, r(1, p, -1) + (a[1] == p ? 0 : p));
  cout << ans << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXV; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXV; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
