#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, MOD = 1e9 + 7;
int tally[MAX + 1];
ll fac[MAX + 1], ifac[MAX + 1];
ll mobius[MAX + 1];

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

int main() {
  fast_io();
  
   // Precompute Mobius function values
  for (int i = 1; i <= MAX; i++) mobius[i] = 1;
  for (int i = 2; i * i <= MAX; i++) {
    if (mobius[i] == 1) {
      for (int j = i; j <= MAX; j += i) mobius[j] *= -i;
      for (int j = i * i; j <= MAX; j += i * i) mobius[j] = 0;
    }
  }
  for (int i = 2; i <= MAX; i++) {
    if (mobius[i] == i) mobius[i] = 1;
    else if (mobius[i] == -i) mobius[i] = -1;
    else if (mobius[i] < 0) mobius[i] = 1;
    else if (mobius[i] > 0) mobius[i] = -1;
  }

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX] = lpow(fac[MAX], MOD - 2, MOD);
  for (int i = MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int n, k, x;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> x;
    tally[x]++;
  }

  ll ans = 0;
  for (int i = 1; i <= MAX; i++) {
    int ccnt = 0;
    for (int j = i; j <= MAX; j += i) ccnt += tally[j];
    ll addend = (mobius[i] + MOD) * C(ccnt, k);
    ans = (ans + addend) % MOD;
  }

  cout << ans << '\n';
}
