#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
const ll INF = 1e18;
int a[MAX + 1];
ll pf[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  for (int i = 1; i <= n; i++) pf[i] = pf[i - 1] + a[i];

  ll ans = 0, diff = INF;
  for (int e = 1; e <= n; e++) {
    for (int s = e; s >= 1; s--) {
      ll sum = pf[e] - pf[s - 1];
      auto it = upper_bound(pf + e, pf + n + 1, pf[e] + sum);

      if (it != pf + n + 1) {
        ll num = *it - pf[e];
        if (abs(num - sum) < diff) {
          diff = abs(num - sum);
          ans = sum + num;
        }
        else if (abs(num - sum) == diff && sum + num > ans) ans = sum + num;
      }
      ll num = *(--it) - pf[e];
      if (abs(num - sum) < diff) {
        diff = abs(num - sum);
        ans = sum + num;
      }
      else if (abs(num - sum) == diff && sum + num > ans) ans = sum + num;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
