#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
int lb[MAX], ub[MAX], a[MAX], b[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
    lb[i] = a[i] - b[i], ub[i] = a[i] + b[i];
  }
  sort(lb, lb + n);
  sort(ub, ub + n);

  for (int i = 0; i < n; i++) {
    auto lt = lower_bound(ub, ub + n, a[i] - b[i]);
    auto ut = upper_bound(lb, lb + n, a[i] + b[i]);

    cout << lt - ub + 1 << ' ' << ut - lb << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
