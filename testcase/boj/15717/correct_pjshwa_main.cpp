#include <bits/stdc++.h>
#define ll long long
#define MOD int(1e9 + 7)
using namespace std;

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

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll n;
  cin >> n;
  if (n == 0) cout << "1\n";
  else cout << lpow(2, n - 1, MOD) << '\n';
}
