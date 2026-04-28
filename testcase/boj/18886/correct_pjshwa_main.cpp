#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 2.5e5;
int MOD;
ll fac[MAX + 1];

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

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n >> MOD;

  fac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ll cur = n - i;
    cur = (cur * fac[i + 1]) % MOD;
    cur = (cur * fac[n - i]) % MOD;
    ans = (ans + cur) % MOD;
  }

  cout << ans << '\n';
}
