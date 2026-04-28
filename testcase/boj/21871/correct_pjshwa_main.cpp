#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  ll n, k;
  cin >> n >> k;

  ll ans = n * n;

  ll s = min(n + 1, (k + 1) / 2);
  ans += s * s;
  ans += (n - s + 1) * k;
  ans *= 2;

  ans--;
  if (k <= 2 * n && k % 2 == 0) ans -= (2 * (k / 2) - 1);

  cout << ans;
}
