#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX + 1], b[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  for (int i = 1; i <= n; i++) a[i] = b[i] - a[i];

  if (n == 1) return cout << "YES\n", void();
  if (n == 2) {
    if (a[1] >= 1 && a[2] == 0) cout << "YES\n";
    else cout << "NO\n";
    return;
  }

  ll cnt = 0;
  for (int i = 1; i <= n; i++) cnt += a[i];

  if (a[1] >= 1 && cnt >= n - 1) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
