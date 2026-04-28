#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll B, X, Y, ans = 0, pw = 1; cin >> B >> X >> Y;
  while (X || Y) {
    ll Xd = X % B, Yd = Y % B;
    ll d = (Xd + Yd) % B;
    ans += pw * d;
    pw *= B; X /= B; Y /= B;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
