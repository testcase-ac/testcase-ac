#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
pii a[MAX];

void solve() {
  int p, n;
  cin >> p >> n;
  for (int i = 0; i < n; ++i) cin >> a[i].first, a[i].second = -i;
  sort(a, a + n);

  vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    int pay = min(p / (n - i), a[i].first);
    p -= pay;
    ans[-a[i].second] = pay;
  }

  if (p) cout << "IMPOSSIBLE";
  else for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
