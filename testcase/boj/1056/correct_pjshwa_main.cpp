#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll lpow(ll x, ll y, ll m){
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

// 2 <= x <= 62, binary search the base for each x
int main() {
  fast_io();

  ll n;
  cin >> n;

  ll long_max = 9223372036854775807;
  ll min_dist = 1e18;
  ll a, b;
  for (int i = 2; i <= 60; i++) {
    ll left = 2, right = log(long_max) / log(i);
    // ll mid = (left + right) / 2;
    // ll cur;

    // while (left < right) {
    //   cur = lpow(i, mid, 1e18);

    //   if (cur < n) right = mid;
    //   else left = mid + 1;

    //   mid = (left + right) / 2;
    // }
    while (lpow(left, i, 1e18) < n) left++;
    a = lpow(left, i, 1e18);
    b = lpow(left - 1, i, 1e18);
    // cout << i << ' ' << left << ' ' << endl;
    if (min(a - n, n - b) + left < min_dist) cout << i << ' ' << left << ' ' << endl;
    min_dist = min(min_dist, min(a - n, n - b) + left);
  }
  min_dist = min(min_dist, n - 1);
  cout << min_dist << endl;
}
