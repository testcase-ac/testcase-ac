#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll a[MAX], m;

void r(ll n, ll mul) {
  while (n % 2 == 0) n /= 2, mul *= 2;
  while (n % 3 == 0) n /= 3, mul *= 3;
  if (n == 1) a[++m] = mul;
  else {
    ll x; for (x = 3; x * 3 < n; x *= 3);
    a[++m] = mul * x;
    r(n - x, mul);
  }
}

void solve() {
  ll n;
  cin >> n;
  m = 0;

  r(n, 1);
  cout << m << '\n';
  for (int i = 1; i <= m; i++) cout << a[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
