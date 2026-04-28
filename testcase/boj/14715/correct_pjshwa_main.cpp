#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, cnt = 0;
  cin >> n;
  for (int i = 2; i <= n; i++) {
    while (n % i == 0) {
      n /= i;
      cnt++;
    }
  }

  int ans = 0, pow = 1;
  while (pow < cnt) {
    ans++;
    pow *= 2;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
