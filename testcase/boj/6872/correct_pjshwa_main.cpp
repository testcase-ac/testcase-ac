#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B;
  cin >> A >> B;

  int ans = 0;
  for (int i = A; i <= B; i++) {
    int cnt = 0;
    for (int j = 1; j * j <= i; j++) {
      if (i % j) continue;

      cnt++;
      if (j * j != i) cnt++;
    }

    if (cnt == 4) ans++;
  }

  cout << "The number of RSA numbers between " << A << " and " << B << " is " << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
