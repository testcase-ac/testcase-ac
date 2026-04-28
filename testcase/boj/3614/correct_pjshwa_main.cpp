#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  int ans = 0;
  for (int g = 1; g <= N; g++) {
    if (N % g) continue;

    int u = N / g + 1;
    for (int a = 1; a < u; a++) {
      int b = u - a;
      if (b < a) break;
      if (__gcd(a, b) == 1) ans++;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
