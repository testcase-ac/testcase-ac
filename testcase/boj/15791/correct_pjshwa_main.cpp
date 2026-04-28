#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll lpow(ll x, ll y, ll m){
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

  int n, m;
  ll nom = 1, denom = 1;
  cin >> n >> m;

  int mod = 1e9 + 7;
  for (int i = 0; i < m; i++) {
    nom = (nom * (n - i)) % mod;
    denom = (denom * (i + 1)) % mod;
  }

  cout << (nom * lpow(denom, mod - 2, mod)) % mod << '\n';
}
