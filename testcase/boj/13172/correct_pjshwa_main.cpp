#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int mod = 1e9 + 7;

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
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int m;
  ll ni, si, ts = 0;
  cin >> m;

  while (m--) {
    cin >> ni >> si;
    ts += si * lpow(ni, mod - 2, mod);
    ts %= mod;
  }
  cout << ts << '\n';
}
