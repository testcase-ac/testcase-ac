#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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

const int MAX = 1e5, MOD = 235813;
int a[MAX];
ll coef[MAX];

int conv(ll a) {
  if (a < 0) return MOD - (abs(a) % MOD);
  else return a % MOD;
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  coef[0] = 1;
  for (int i = 1; i < n; i++) {
    coef[i] = (coef[i - 1] * (n - i)) % MOD;
    coef[i] = (coef[i] * lpow(i, MOD - 2, MOD)) % MOD;
  }

  int oans = 0;
  for (int i = 0; i < n; i++) {
    int sign = (i & 1) ? -1 : 1;
    ll term = coef[n - 1 - i] * a[n - 1 - i] * sign;
    oans = (oans + conv(term)) % MOD;
  }
  if (oans == 0) return cout << 0, 0;

  int cnt = 0;
  for (int i = 0; i < n; i++) {
    int sign = (i & 1) ? -1 : 1;
    ll term = coef[n - 1 - i] * a[n - 1 - i] * sign;
    int cans = (oans + MOD - conv(term)) % MOD;
    int target = (lpow(coef[n - 1 - i], MOD - 2, MOD) * cans) % MOD;
    target = min(target, MOD - target);
    if (target <= 1e5) cnt++;
  }

  cout << cnt;
}
