#include <bits/stdc++.h>
#define ll long long
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

  int n, c, k;
  cin >> n;

  ll val, sum = 0;
  ll mod = 1e9 + 7;
  for (int i = 0; i < n; i++) {
    cin >> c >> k;
    if (k) {
      val = c;
      val = val * k % mod;
      val = val * lpow(2, k - 1, mod) % mod;
      sum = (sum + val) % mod;
    }
  }

  cout << sum << '\n';
}
