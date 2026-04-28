#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int abi[1000];

void solve() {
  int n, d, k;
  cin >> n >> d >> k;
  for (int i = 0; i < n; i++) {
    int qi;
    cin >> qi;
    while (qi--) {
      int ai;
      cin >> ai;
      abi[i] |= (1 << (ai - 1));
    }
  }

  int ans = 0;
  for (int state = 0; state < (1 << d); state++) {
    if (__builtin_popcount(state) > k) continue;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
      if ((abi[i] | state) == state) cnt++;
    }
    ans = max(ans, cnt);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
