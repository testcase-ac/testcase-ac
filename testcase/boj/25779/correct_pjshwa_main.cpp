#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 14;
ll P[MAX];

void solve() {
  ll n, k;
  cin >> n >> k;
  for (int i = 0; i < k; i++) cin >> P[i];

  ll left = 1, right = 1e18;
  while (left < right) {
    ll mid = (left + right) / 2, cnt = mid;
    for (int s = 1; s < (1 << k); s++) {
      int parity = __builtin_popcount(s) % 2 ? -1 : 1;
      ll dem = 1;
      for (int i = 0; i < k; i++) {
        if (s & (1 << i)) dem *= P[i];
      }
      cnt += parity * mid / dem;
    }

    if (cnt < n) left = mid + 1;
    else right = mid;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
