#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void print(__int128_t n) {
  if (n < 0) {
    cout << '-';
    n = -n;
  }
  if (n >= 10) print(n / 10);
  cout << char(n % 10 + '0');
}

void solve() {
  ll n;
  cin >> n;

  __int128_t ans = 0, pw = 5;
  while (pw <= n) {
    __int128_t w = n / pw;
    ans += w * (w - 1) / 2 * pw;
    ans += w * (n % pw + 1);
    pw *= 5;
  }
  print(ans); cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
