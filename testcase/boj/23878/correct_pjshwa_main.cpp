#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, tt = 0;
  string s;
  cin >> n >> s;

  int lg1 = -1, lg2 = -1, lh1 = -1, lh2 = -1;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'G') {
      lg1 = lg2, lg2 = i;
      if (i < 2) continue;
      if (lg2 - lg1 > 2) ans += (min(i - 2, lg2) - lg1);
      else ans += (min(i - 2, lh2) - lh1);
    }
    if (s[i] == 'H') {
      lh1 = lh2, lh2 = i;
      if (i < 2) continue;
      if (lh2 - lh1 > 2) ans += (min(i - 2, lh2) - lh1);
      else ans += (min(i - 2, lg2) - lg1);
    }
  }
  cout << ans << '\n';
}
