#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], b[MAX];
bool vis[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> b[i];

  memset(a, -1, sizeof(a));
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    a[x - 1] = y;
    vis[y] = 1;
  }

  int v = 1, last = 0;
  for (int i = 0; i < n; i++) {
    if (b[i] == 0) continue;

    for (int j = i; j >= last; j--) {
      if (a[j] != -1) continue;

      while (vis[v]) v++;
      a[j] = v++;
    }

    last = i + 1;
  }

  int cmax = 0;
  for (int i = 0; i < n; i++) {
    cmax = max(cmax, a[i]);

    if (b[i] && cmax != i + 1) return cout << "-1\n", void();
    if (!b[i] && cmax == i + 1) return cout << "-1\n", void();
  }

  for (int i = 0; i < n; i++) cout << a[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
