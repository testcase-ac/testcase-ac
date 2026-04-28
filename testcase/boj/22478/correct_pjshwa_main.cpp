#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// How many digits upto n?
ll f(ll n) {
  __int128_t p = 1, d = 0, u = 1;
  while (10 * p <= n) {
    // count multiples of 3 and 5 in range [p, 10p)
    ll cnt3 = (10 * p - 1) / 3 - (p - 1) / 3;
    ll cnt5 = (10 * p - 1) / 5 - (p - 1) / 5;
    ll cnt15 = (10 * p - 1) / 15 - (p - 1) / 15;

    d += 4 * (cnt3 + cnt5);
    d += u * (9 * p - cnt3 - cnt5 + cnt15);

    p *= 10; u++;
  }

  ll cnt3 = n / 3 - (p - 1) / 3;
  ll cnt5 = n / 5 - (p - 1) / 5;
  ll cnt15 = n / 15 - (p - 1) / 15;

  d += 4 * (cnt3 + cnt5);
  d += u * (n - p + 1 - cnt3 - cnt5 + cnt15);
  return d;
}

void solve() {
  ll s; cin >> s;

  ll left = 1, right = s + 1;
  while (left < right) {
    ll mid = (left + right) / 2;
    if (f(mid) < s) left = mid + 1;
    else right = mid;
  }

  ll sx = left - 1, sv = f(sx);
  string ref = "";
  for (ll i = sx + 1; i <= sx + 50; i++) {
    if (i % 3 == 0 || i % 5 == 0) {
      if (i % 3 == 0) ref += "Fizz";
      if (i % 5 == 0) ref += "Buzz";
    }
    else ref += to_string(i);
  }

  for (ll i = s; i < s + 20; i++) cout << ref[i - sv - 1];
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
