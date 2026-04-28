#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];
int candidates[12] = {202021, 20202021, 202002021, 202012021, 202022021, 202032021, 202042021, 202052021, 202062021, 202072021, 202082021, 202092021};

void solve() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 12; j++) {
      auto [l, r] = equal_range(a + i + 1, a + n, candidates[j] - a[i]);
      ans += (r - l);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
