#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1e6;
int a[MAX], b[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];

  int ans = 0;
  for (int i = 0; i < n - 1; i++) {
    if (a[i] == b[i]) continue;

    int x = a[i] ^ b[i];
    a[i] ^= x;
    a[i + 1] ^= x;
    ans++;
  }

  if (a[n - 1] == b[n - 1]) cout << ans << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
