#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], b[MAX], inv[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i], inv[b[i]] = i;
  for (int i = 0; i < n; i++) a[i] = inv[a[i]];

  int ans = 0, run = -1;
  for (int i = 0; i < n; i++) {
    if (a[i] > run) run = a[i];
    else ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
