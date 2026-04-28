#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

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

ll phi(ll n) {
  ll result = n;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      result -= result / i;
    }
  }
  if (n > 1) result -= result / n;
  return result;
}

void solve() {
  int N, E, C;
  cin >> N >> E >> C;

  int P, Q;
  for (int i = 2;; i++) {
    if (N % i == 0) {
      P = i, Q = N / i;
      break;
    }
  }
  int ph1 = (P - 1) * (Q - 1);
  int ph2 = phi(ph1);
  int D = lpow(E, ph2 - 1, ph1);
  cout << lpow(C, D, N) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
