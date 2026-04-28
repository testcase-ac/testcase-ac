#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n, k, s;
  cin >> n >> k;
  k = min(k, n - 1);
  s = n - k - 1;
  cout << (n * n + n - s * s - s) * 2 << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
