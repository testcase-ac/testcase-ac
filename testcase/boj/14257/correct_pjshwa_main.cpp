#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int bx[50];
int main() {
  fast_io();

  ll s, x;
  cin >> s >> x;

  bool flag = s == x;

  int i = 0;
  while (x) {
    bx[i++] = x & 1;
    x >>= 1;
  }

  int cnt = 0;
  for (int ix = 49; ix >= 0; ix--) {
    if (bx[ix]) {
      cnt++;
      s -= (1LL << ix);
    }
    else if (s >= (1LL << (ix + 1))) s -= (1LL << (ix + 1));
  }

  ll ans = 0;
  if (s == 0) {
    ans = 1LL << cnt;
    if (flag) ans -= 2;
  }
  cout << ans << '\n';
}
