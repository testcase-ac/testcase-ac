#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[8];

ll lcm(ll a, ll b) {
  return a / __gcd(a, b) * b;
}

int t[60];

void solve() {
  int k, n;
  cin >> k >> n;

  int mvalue = 1e9;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    mvalue = min(mvalue, a[i]);
    assert(!t[a[i]]);
    t[a[i]]++;
    assert(3 <= a[i] && a[i] <= 40);
  }
  assert(1 <= k && k < mvalue);
  assert(2 <= n && n <= 8);

  ll l = 1;
  for (int i = 0; i < n; i++) l = lcm(l, a[i]);
  cout << l - k << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
