#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll upto(ll n) {
  if (n == 0) return 0;

  ll q = sqrt(n), ret = 0;
  for (ll i = 1; i <= q; i++) {
    if (i & 1) ret -= (n / i);
    else ret += (n / i);
  }

  ll last = n;
  for (ll i = 1; i < n / q; i++) {
    ll s = n / (i + 1) + 1;
    ll diff = last - s + 1;
    if (diff & 1) {
      if (last & 1) ret -= i;
      else ret += i;
    }
    last = s - 1;
  }

  return ret;
}

void solve() {
  ll S, T;
  cin >> S >> T;
  cout << upto(T) - upto(S - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
