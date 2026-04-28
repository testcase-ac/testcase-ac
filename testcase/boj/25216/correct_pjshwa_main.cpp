#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXN = 5000, MAXT = 100;
tuple<int, int, int, int> a[MAXN + 1];
vector<int> graph[MAXN + 1];
int d[MAXN + 1][MAXT + 1], T;
ll D;
bool flag = true;

int r(int v, int t) {
  if (d[v][t] != -1) return d[v][t];
  if (t == T) return d[v][t] = 0;

  int res = 0;
  auto& [ai, xi, yi, ci] = a[v];
  if (flag || ai + xi * t <= D * yi) {
    for (int u : graph[v]) res = max(res, r(u, t + 1));
    res += ci;
  }
  return d[v][t] = res;
}

void solve() {
  int n, m;
  cin >> n >> m >> T;
  for (int i = 1; i <= n; i++) {
    int x, y, z, w;
    cin >> x >> y >> z >> w;
    a[i] = {x, y, z, w};
  }
  for (int i = 1; i <= m; i++) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
  }

  memset(d, -1, sizeof(d));
  int maxv = r(1, 0);
  flag = false;

  ll left = 0, right = 1e12;
  while (left < right) {
    D = (left + right) / 2;
    memset(d, -1, sizeof(d));
    if (r(1, 0) == maxv) right = D;
    else left = D + 1;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
