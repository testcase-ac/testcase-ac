#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll lcm(ll a, ll b) {
  return a / __gcd(a, b) * b;
}

ll H, W;
void solve() {
  ll l = lcm(H, W);
  ll ans = (l / H) * (l / W);
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> H >> W) {
    if (H == 0 && W == 0) break;
    solve();
  }
}
