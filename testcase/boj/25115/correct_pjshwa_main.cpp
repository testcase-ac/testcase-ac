#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1e6;
ll a[MAX], n;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool check(ll use) {
  ll bonus = 0;
  bool f = false;

  for (int i = 0; i < n; i++) {
    if (a[i] <= use) {
      use -= a[i];
      bonus += a[i] / 10;
    }
    else {
      if (f) {
        if (a[i] > bonus) return false;
        bonus -= a[i];
      }
      else {
        if (bonus < a[i] - use) return false;
        bonus -= a[i] - use;
        bonus += use / 10;
        use = 0;
        f = true;
      }
    }
  }

  return true;
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i], a[i] *= 10;

  ll left = 0, right = 1e16;
  while (left < right) {
    ll mid = (left + right) / 2;
    if (check(mid * 10)) right = mid;
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
