#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int primes[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

void solve() {
  ll n;
  cin >> n;

  int pp = 0;
  __int128_t pw = 1;
  while (pw * primes[pp] <= n) {
    pw *= primes[pp];
    pp++;
  }

  ll a = 1, b = pw;
  for (int i = 0; i < pp; i++) a *= primes[i] - 1;
  ll g = __gcd(a, b);
  cout << (b - a) / g << '/' << b / g << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
