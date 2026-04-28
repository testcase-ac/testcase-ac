#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
ll fac[MAX + 1], ifac[MAX + 1];
ll n, m, k, p;
 
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

  cin >> n >> m >> k >> p;

  fac[0] = ifac[0] = 1;
  for (int i = 1; i < p; i++) fac[i] = fac[i - 1] * i % p;
  ifac[p - 1] = lpow(fac[p - 1], p - 2, p);
  for (int i = p - 2; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % p;

  ll ans = 0;
  for (int i = 0; i <= n; i++) {
    if (k < i) break;
    if ((k - i) & 1) continue;

    ll cur = Lucas(n, i, p);
    cur = (cur * Lucas(n + m + (k - i) / 2 - 1, (k - i) / 2, p)) % p;
    ans = (ans + cur) % p;
  }

  cout << ans << '\n';
}
