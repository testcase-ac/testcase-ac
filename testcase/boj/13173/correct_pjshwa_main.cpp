#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

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

int main() {
  fast_io();

  ll P, Q, N, K;
  cin >> P >> Q >> N >> K;
  if (K == 0) cout << 0;
  else if (K == N) cout << 1;
  else if (Q == 0) cout << 1;
  else if (Q == P) cout << 0;
  else if (P == 2 * Q) cout << (K * lpow(N, mod - 2, mod)) % mod;
  else {
    ll S = (Q * lpow(P - Q, mod - 2, mod)) % mod;
    ll S1 = (lpow(S, K, mod) + mod - 1) % mod;
    ll S2 = (lpow(S, N, mod) + mod - 1) % mod;
    cout << (S1 * lpow(S2, mod - 2, mod)) % mod;
  }
}
