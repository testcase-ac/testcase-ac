#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, k, mod;
  cin >> n >> k;

  if (2 * n < k * (k + 1)) cout << -1;
  else {
    mod = (k * (k + 1) / 2) % k;
    if (n % k == mod) cout << k - 1;
    else cout << k;
  }
  cout << '\n';
}
