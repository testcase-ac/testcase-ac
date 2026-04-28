#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

namespace miller_rabin {
  ll mul(ll a, ll b, ll p){
    ll ret = 0;
    while(a){
      if(a&1) ret = (ret + b) % p;
      a >>= 1;
      b = (b << 1) % p;
    }
    return ret;
  }
  ll ipow(ll x, ll y, ll p){
    ll ret = 1, piv = x % p;
    while(y){
      if(y&1) ret = mul(ret, piv, p);
      piv = mul(piv, piv, p);
      y >>= 1;
    }
    return ret;
  }
  bool miller_rabin(ll x, ll a){
    if(x % a == 0) return 0;
    ll d = x - 1;
    while(1){
      ll tmp = ipow(a, d, x);
      if(d&1) return (tmp != 1 && tmp != x-1);
      else if(tmp == x-1) return 0;
      d >>= 1;
    }
  }
  bool isprime(ll x) {
    if (x == 2) return 1;
    else if (x % 2 == 0) return 0;

    vector<int> opr{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (auto &i : opr) {
      if(x == i) return 1;
      if(x > opr.back() && miller_rabin(x, i)) return 0;
    }
    if (x <= opr.back()) return 0;
    return 1;
  }
}

void solve() {
  ll a, b;
  cin >> a >> b;
  for (ll i = a; i <= b; i++) {
    if (i == 9 || miller_rabin::isprime(i)) cout << i << " ";
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
