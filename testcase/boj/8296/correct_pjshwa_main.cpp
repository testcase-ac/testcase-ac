#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  vector<bool> linc(n), ldec(n), rinc(n), rdec(n);
  linc[0] = ldec[0] = rinc[n - 1] = rdec[n - 1] = 1;
  for (int i = 1; i < n; i++) {
    linc[i] = linc[i - 1] && a[i] >= a[i - 1];
    ldec[i] = ldec[i - 1] && a[i] <= a[i - 1];
  }
  for (int i = n - 2; i >= 0; i--) {
    rinc[i] = rinc[i + 1] && a[i] >= a[i + 1];
    rdec[i] = rdec[i + 1] && a[i] <= a[i + 1];
  }

  if (linc[n - 1] || ldec[n - 1] || rinc[0] || rdec[0]) return cout << "TAK\n", void();
  for (int i = 1; i < n - 1; i++) {
    if (linc[i] && rdec[i + 1] && a[n - 1] <= a[0]) return cout << "TAK\n", void();
    if (ldec[i] && rinc[i + 1] && a[n - 1] >= a[0]) return cout << "TAK\n", void();
  }
  cout << "NIE\n";
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
