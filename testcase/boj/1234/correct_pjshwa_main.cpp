#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, c[3];
ll ans, cur = 1, fac[11];

void dfs(int i) {
  if (i == 0) {
    ans += cur;
    return;
  }

  for (int& color : c) {
    if (color >= i) {
      color -= i;
      dfs(i - 1);
      color += i;
    }
  }

  if (i % 2 == 0) {
    if (c[0] >= i / 2 && c[1] >= i / 2) {
      c[0] -= i / 2;
      c[1] -= i / 2;
      cur *= (fac[i] / fac[i / 2] / fac[i / 2]);
      dfs(i - 1);
      cur /= (fac[i] / fac[i / 2] / fac[i / 2]);
      c[0] += i / 2;
      c[1] += i / 2;
    }

    if (c[0] >= i / 2 && c[2] >= i / 2) {
      c[0] -= i / 2;
      c[2] -= i / 2;
      cur *= (fac[i] / fac[i / 2] / fac[i / 2]);
      dfs(i - 1);
      cur /= (fac[i] / fac[i / 2] / fac[i / 2]);
      c[0] += i / 2;
      c[2] += i / 2;
    }

    if (c[1] >= i / 2 && c[2] >= i / 2) {
      c[1] -= i / 2;
      c[2] -= i / 2;
      cur *= (fac[i] / fac[i / 2] / fac[i / 2]);
      dfs(i - 1);
      cur /= (fac[i] / fac[i / 2] / fac[i / 2]);
      c[1] += i / 2;
      c[2] += i / 2;
    }
  }

  if (i % 3 == 0) {
    for (int& color : c) if (color < i / 3) return;

    for (int& color : c) color -= i / 3;
    cur *= (fac[i] / fac[i / 3] / fac[i / 3] / fac[i / 3]);
    dfs(i - 1);
    cur /= (fac[i] / fac[i / 3] / fac[i / 3] / fac[i / 3]);
    for (int& color : c) color += i / 3;
  }
}

void solve() {
  cin >> n;
  for (int i = 0; i < 3; i++) cin >> c[i];

  fac[0] = 1;
  for (int i = 1; i <= 10; i++) fac[i] = fac[i - 1] * i;

  dfs(n);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
