#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  int ans = 0;
  for (int b = 1; b <= MAX; b++) {
    int fbasket = 0;
    for (int i = 0; i < n; i++) fbasket += a[i] / b;

    if (fbasket < k / 2) continue;
    if (fbasket >= k) {
      ans = max(ans, b * k / 2);
      continue;
    }

    int res = b * (fbasket - k / 2);
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) pq.push(a[i] % b);

    while (fbasket < k) {
      res += pq.top();
      pq.pop();
      fbasket++;
    }

    ans = max(ans, res);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
