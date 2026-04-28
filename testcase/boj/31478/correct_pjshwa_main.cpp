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
  int A, B, C, K, L; cin >> A >> B >> C >> K >> L;
  L = (L - K + 7) % 7;

  int ans = 0;
  if (lpow(B, C, 7) == (A * L) % 7) ans ^= 2;

  int pw = lpow(B, C, 6);
  if (lpow(A, pw, 7) == L) ans ^= 1;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
