#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  ll n;
  cin >> n;

  n = ceil(sqrt(n) * 2 / 3);
  cout << n << '\n';
  
  int w[4] = {1, 2, 3, 5}, j = 0;
  ll o = 0, prv = 1;
  for (int i = 0; i < n; i++) {
    ll cur = o * 6 + w[j++];
    cout << prv * cur << ' ';
    prv = cur;
    if (j == 4) j = 0, o++;
  }
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
