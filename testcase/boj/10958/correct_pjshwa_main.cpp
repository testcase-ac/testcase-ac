#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll a[40], msum[1 << 20];

int main() {
  fast_io();

  int n;
  ll s;
  cin >> n >> s;
  for (int i = 0; i < n; i++) cin >> a[i];

  int h = n / 2, r = n - h;
  for (int i = 0; i < (1 << h); i++) {
    for (int j = 0; j < h; j++) {
      if (i & (1 << j)) msum[i] += a[j];
    }
  }
  sort(msum, msum + (1 << h));

  ll ans = 0;
  for (int i = 0; i < (1 << r); i++) {
    ll cur = 0;
    for (int j = 0; j < r; j++) {
      if (i & (1 << j)) cur += a[h + j];
    }
    ans += upper_bound(msum, msum + (1 << h), s - cur) - msum;
  }
  cout << ans << '\n';
}
