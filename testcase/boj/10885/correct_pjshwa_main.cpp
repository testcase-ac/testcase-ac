#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
int a[100000];
int main() {
  fast_io();

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    int me = -3;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      me = max(me, a[i]);
    }

    int ntc = 0, mtc = 0;
    bool sign = true;

    for (int i = 0; i < n; i++) {
      if (abs(a[i]) == 2) ntc++;
      if (a[i] < 0) sign = !sign;
      if (a[i] == 0) {
        sign = true, ntc = 0;
        continue;
      }

      if (sign) me = 1, mtc = max(mtc, ntc);
    }

    ntc = 0, sign = true;
    for (int i = n - 1; i >= 0; i--) {
      if (abs(a[i]) == 2) ntc++;
      if (a[i] < 0) sign = !sign;
      if (a[i] == 0) {
        sign = true, ntc = 0;
        continue;
      }

      if (sign) me = 1, mtc = max(mtc, ntc);
    }

    if (!mtc) cout << me << '\n';
    else {
      ll ans = 1;
      while (mtc--) ans = (ans * 2) % MOD;
      cout << ans << '\n';
    }
  }
}
