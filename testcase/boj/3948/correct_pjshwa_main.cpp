#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll a[21];
ll C(int n, int k) {
  ll ans = 1;
  for (int i = 1; i <= k; i++) {
    ans *= (n - i + 1);
    ans /= i;
  }
  return ans;
}

void solve() {
  int n;
  cin >> n;

  if (n == 1) cout << "1\n";
  else cout << 2 * a[n] << '\n';
}

int main() {
  fast_io();

  a[0] = a[1] = 1;
  for (int i = 2; i <= 20; i++) {
    for (int j = 0; j < i; j++) a[i] += C(i - 1, j) * a[j] * a[i - 1 - j];
    a[i] /= 2;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
