#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
ll a[MAX + 1], t[MAX + 1], pf[MAX + 1];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0, x; i < k; i++) {
    cin >> x;
    t[x]++;
  }

  for (int i = 1; i <= MAX; i++) {
    for (int j = 0; j < n; j += i) a[j] += t[i];
  }

  pf[0] = a[0];
  for (int i = 1; i < n; i++) {
    pf[i] = pf[i - 1] + a[i];
  }

  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    if (l) cout << pf[r] - pf[l - 1] << '\n';
    else cout << pf[r] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
