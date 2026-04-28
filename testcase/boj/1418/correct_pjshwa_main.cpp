#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int d = i;
    for (int j = 2; j <= k; j++) {
      while (d % j == 0) d /= j;
    }
    if (d == 1) ans++;
  }

  cout << ans << '\n';
}
