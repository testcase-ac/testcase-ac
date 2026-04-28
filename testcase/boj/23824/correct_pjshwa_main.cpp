#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1048573;
ll fac[MOD + 1], ifac[MOD + 1];

//Computes C(N,R) modulo P in O(log(n)) time.
ll Lucas(ll N,ll R,int P) {
  if(R<0||R>N) return 0;
  if(R==0||R==N) return 1;
  
  if(N>=P) return (Lucas(N/P,R/P,P)*Lucas(N%P,R%P,P))%P;
  return (fac[N]*(ifac[N-R]*ifac[R])%P)%P;
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

void solve() {
  ll k, a, n;
  cin >> k >> a >> n;

  ll ans = 0, pl = (1LL << k);
  for (int i = 0; i <= a; i++) {
    if (n < pl * i) break;

    ll cur = Lucas(a, i, MOD);
    if (i & 1) cur = MOD - cur;

    ll j = n - pl * i;
    cur = (cur * Lucas(a + j - 1, j, MOD)) % MOD;
    ans = (ans + cur) % MOD;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i < MOD; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MOD - 1] = lpow(fac[MOD - 1], MOD - 2, MOD);
  for (int i = MOD - 2; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
