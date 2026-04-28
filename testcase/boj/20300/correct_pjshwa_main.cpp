#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000;
ll a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  ll loss = 0;
  if (n & 1) {
    loss = a[n - 1];
    for (int i = 0; i < n / 2; i++) loss = max(loss, a[i] + a[n - 2 - i]);
  }
  else for (int i = 0; i < n / 2; i++) loss = max(loss, a[i] + a[n - 1 - i]);
  cout << loss << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
