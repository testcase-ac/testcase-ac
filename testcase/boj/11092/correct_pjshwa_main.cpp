#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 15;
int a[MAX];

int cross(int r) {
  if (r == 0) return a[0];
  if (r == 1) return a[1];
  if (r == 2) return a[0] + a[1] + a[2];

  if (a[0] + a[r - 1] > 2 * a[1]) return a[0] + 2 * a[1] + a[r] + cross(r - 2);
  else return 2 * a[0] + a[r - 1] + a[r] + cross(r - 2);
}

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  sort(a, a + n);
  cout << cross(n - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
