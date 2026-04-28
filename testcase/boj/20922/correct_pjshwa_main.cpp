#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int a[MAX], t[100'001];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  int ep = 0, ans = 0;
  for (int sp = 0; sp < n; sp++) {
    while (ep < n && t[a[ep]] < k) t[a[ep++]]++;
    ans = max(ans, ep - sp);
    t[a[sp]]--;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
