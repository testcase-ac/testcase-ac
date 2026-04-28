#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < 2 * n; i++) cin >> a[i];
  sort(a, a + 2 * n);

  int mvalue = 1e9;
  for (int i = 0; i < n; i++) mvalue = min(mvalue, a[i] + a[2 * n - 1 - i]);
  cout << mvalue << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
