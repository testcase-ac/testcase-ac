#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

pll ext_gcd(ll a, ll b) {
  if (b) {
    auto tmp = ext_gcd(b, a % b);
    return {tmp.second, tmp.first - (a / b) * tmp.second};
  } else return {1, 0};
}

void solve() {
  ll M, b; cin >> M >> b;

  for (int m = 2; m <= M; m++) for (int a = 1; a <= M; a++) {
    bool f = false;
    for (int x = 0; x < m; x++) {
      if (a * x % m == b % m) {
        f = true;
        break;
      }
    }

    if (f) cout << m << ' ' << a << endl;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
