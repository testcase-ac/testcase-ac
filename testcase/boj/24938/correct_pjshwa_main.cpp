#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
ll a[MAX];

void solve() {
  int n;
  cin >> n;

  ll sum = 0;
  for (int i = 0; i < n; i++) cin >> a[i], sum += a[i];

  ll avg = sum / n, ans = 0;
  for (int i = 0; i < n - 1; i++) {
    ll def = avg - a[i];
    a[i + 1] -= def, a[i] += def;
    ans += abs(def);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
