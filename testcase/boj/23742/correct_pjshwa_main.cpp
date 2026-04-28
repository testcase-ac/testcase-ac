#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  reverse(a, a + n);

  ll rsum = 0;
  int i = 0;
  while (i < n) {
    if ((rsum + a[i]) * (i + 1) >= rsum * i + a[i]) rsum += a[i++];
    else break;
  }

  ll ans = rsum * i;
  for (int j = i; j < n; j++) ans += a[j];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
