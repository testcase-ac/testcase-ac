#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4e5;
int t[MAX + 1];

void solve() {
  for (int i = 1; i <= MAX; i++) {
    for (int j = 1; j * j <= i; j++) {
      if (i % j == 0) {
        int x = j, y = i / j;
        if ((x + y) % 2 == 0) continue;

        // x != y because of above condition
        int b = (x + y - 1) / 2;
        if (x - b > 0 && x <= 2 * b) t[i]++;
        if (y - b > 0 && y <= 2 * b) t[i]++;
      }
    }
  }

  int n;
  cin >> n;
  n <<= 2;

  ll ans = 0;
  for (int j = 1; j * j <= n; j++) {
    if (n % j == 0) {
      ll addend = (ll)t[j] * t[n / j];
      if (j != n / j) addend *= 2;
      ans += addend;
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
