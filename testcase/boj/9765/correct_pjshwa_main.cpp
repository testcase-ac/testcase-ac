#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  ll c1, c2, c3, c4, c5, c6;
  cin >> c1 >> c2 >> c3 >> c4 >> c5 >> c6;

  ll x2 = gcd(c1, c5);
  ll x6 = gcd(c3, c6);
  ll x1 = c1 / x2;
  ll x3 = c5 / x2;
  ll x5 = c6 / x6;
  ll x7 = c3 / x6;

  cout << x1 << ' ' << x2 << ' ' << x3 << ' ' << x5 << ' ' << x6 << ' ' << x7 << '\n';
}
