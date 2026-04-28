#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[20];

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < k; i++) cin >> a[i];

  int ans = 0;
  for (int state = 1; state < (1 << k); state++) {
    ll mul = 1;
    if (__builtin_popcount(state) % 2 == 0) mul = -1;

    __int128_t divid = 1;
    for (int i = 0; i < k; i++) {
      if (state & (1 << i)) {
        divid = lcm(divid, a[i]);
        if (divid > n) break;
      }
    }

    if (divid > n) continue;
    ans += mul * (n / divid);
  }

  cout << ans << '\n';
}
