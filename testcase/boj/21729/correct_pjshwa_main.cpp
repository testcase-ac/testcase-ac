#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MOD = 1e6 + 3;
ll fac[MOD], ifac[MOD];
 
//Computes C(N,R) modulo P in O(log(n)) time.
ll Lucas(ll N,ll R,int P)
{
  if(R<0||R>N)
  {
    return 0;
  }
  
  if(R==0||R==N)
  {
    return 1;
  }
  
  if(N>=P)
  {
    return (Lucas(N/P,R/P,P)*Lucas(N%P,R%P,P))%P;
  }
  
  return (fac[N]*(ifac[N-R]*ifac[R])%P)%P;
}

ll g(ll n) {return (3 * n * n - n) / 2;}

ll calc(ll r, ll c, ll n, ll num) {
  ll mi = (num % 2 == 0 ? 1 : MOD - 1);
  return (mi * (Lucas(r + c - n, r, MOD) + Lucas(c - n - 1, r + 1, MOD))) % MOD;
}

ll mahonian(ll r, ll c) {
  ll res = calc(r, c, 0, 0);
  for (ll num = 1; ; num++) {
    for (ll mul: {1, -1}) {
      ll nxt = g(num * mul);
      if (nxt >= c + 1) return res;
      res = (res + calc(r, c, nxt, num)) % MOD;
    }
  }
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
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < MOD; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MOD - 1] = lpow(fac[MOD - 1], MOD - 2, MOD);
  for (int i = MOD - 2; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  ll tc, n, k;
  cin >> tc;

  while (tc--) {
    cin >> n >> k; 
    cout << mahonian(n - 1, k) << '\n';
  }
}
