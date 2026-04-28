#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n;
  cin >> n;

  for (ll b = 2;; b++) {
    ll c = 1 + b + b * b, last = b * b;
    if (c > n) break;
    for (int pw = 3;; pw++) {
      if (c > n) break;
      if (n % c == 0) {
        cout << pw << '\n';

        ll u = 1, a = n / c;
        for (int j = 0; j < pw; j++) {
          cout << a * u << ' ';
          u *= b;
        }
        return;
      }

      last *= b;
      c += last;
    }
  }
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
