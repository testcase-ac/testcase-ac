#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll fac[20], d[21][21];
ll C(int n, int k) {
  if (n < k) return 0;
  return fac[n] / (fac[k] * fac[n - k]);
}

ll f(int n, int k) {
  if (k == 0) return 1;
  if (n <= 1) return 0;
  if (d[n][k] != -1) return d[n][k];

  ll ret = f(n - 1, k) + f(n - 1, k - 1);
  for (int i = 1; i < n - 1; i++) {
    ll reti = 0;
    for (int j = 0; j < k; j++) reti += f(i, j) * f(n - 1 - i, k - 1 - j);
    ret += C(n - 1, i) * reti;
  }

  return d[n][k] = ret;
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));

  fac[0] = 1;
  for (int i = 1; i < 20; i++) fac[i] = fac[i - 1] * i;

  int n, k, a0;
  cin >> n >> k >> a0;

  ll ans = 0;
  if (a0 == 0) ans = f(n - 1, k);
  else if (a0 == n - 1) ans = f(n - 1, k - 1);
  else for (int i = 0; i < k; i++) ans += f(a0, i) * f(n - 1 - a0, k - 1 - i);

  cout << ans * C(n - 1, a0);
}
