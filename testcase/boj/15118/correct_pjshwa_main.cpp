#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n; cin >> n;

  ll l = 1, r = n + 1;
  ll sum = n * (n - 1) / 2;
  ll p = (sum + 1) / 2;

  ll acc = 0;
  for (int i = 1; i <= n; i++) {
    acc += n - i;
    if (acc >= p) {
      cout << i << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
