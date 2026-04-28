#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
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
  int N, K, P;
  cin >> N >> K >> P;
  if (N == 2) cout << 2 % P << '\n';
  else if (N == 3) {
    if (K == 2) cout << 720 % P << '\n';
    else if (K == 3) {
      ll ans = 1;
      for (int i = 1; i <= 720; i++) ans = (ans * i) % P;
      cout << ans << '\n';
    }
    else cout << "0\n";
  }
  else if (N >= 13 || K >= 3) cout << "0\n";
  else if (N == 12) {
    ll fac = 479001600;
    if (fac >= P) cout << "0\n";
    else {
      ll inv = 1;
      for (int i = fac + 1; i < P; i++) inv = inv * i % P;

      ll ans = P - lpow(inv, P - 2, P);
      cout << ans << '\n';
    }
  }
  else {
    ll fac = 1;
    for (int i = 1; i <= N; i++) fac *= i;

    ll ans = 1;
    for (int i = 1; i <= fac; i++) ans = (ans * i) % P;
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
