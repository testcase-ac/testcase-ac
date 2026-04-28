#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll r(ll n, ll k, bool o) {
  if (n == 1) return 1;

  if (o) {
    if (2 * k <= n) return 2 * k;
    else {
      ll ret = r((n + 1) / 2, k - n / 2, n % 2 == 0);
      return 2 * ret - 1;
    }
  }
  else {
    if (2 * k - 1 <= n) return 2 * k - 1;
    else {
      ll ret = r(n / 2, k - (n + 1) / 2, n & 1);
      return 2 * ret;
    }
  }
}

void solve() {
  ll n, k;
  cin >> n >> k;
  cout << r(n, k, 0) << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
