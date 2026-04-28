#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX], n;

ll upto(ll x) {
  if (x <= 0) return 0;
  return x * (x + 1) / 2;
}

ll get(ll x) {
  ll sum = upto(x);
  for (int i = 0; i < n - 1; i++) {
    int diff = a[i + 1] - a[i];
    sum += upto(x) - upto(x - diff);
  }
  return sum;
}

void solve() {
  ll k;
  cin >> n >> k;
  assert(1 <= n && n <= 1e6);
  assert(1 <= k && k <= 1e18);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    assert(1 <= a[i] && a[i] <= 1e9);
  }

  ll left = 1, right = 2e9;
  while (left < right) {
    ll mid = (left + right) / 2;
    if (get(mid) >= k) right = mid;
    else left = mid + 1;
  }
  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
