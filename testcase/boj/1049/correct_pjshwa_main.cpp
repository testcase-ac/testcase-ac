#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, m, ai, bi, av = 1e9, bv = 1e9;
  cin >> n >> m;

  while (m--) {
    cin >> ai >> bi;
    av = min(av, ai);
    bv = min(bv, bi);
  }

  int ans = ((n - 1) / 6 + 1) * av;
  ans = min(ans, (n / 6) * av + (n - (n / 6) * 6) * bv);
  ans = min(ans, n * bv);
  cout << ans;
}
