#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll upto(ll n) {
  return n * (n + 1) / 2;
}

void solve() {
  ll n, s, k;
  cin >> n >> s >> k;

  ll r = n - k;
  if (upto(k) <= s && s <= upto(n) - upto(r)) {
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= k; i++) ans[i] = 1;

    ll cur = upto(k), p = k;
    while (1) {
      ll diff = s - cur;
      if (diff > r) {
        cur += r;
        swap(ans[p], ans[p + r]);
        p--;
      }
      else {
        swap(ans[p], ans[p + diff]);
        break;
      }
    }

    cout << "YES\n";
    for (int i = 1; i <= n; i++) cout << ans[i];
    cout << '\n';
  }
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
