#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int lcm(int a, int b) {
  return a / __gcd(a, b) * b;
}

int main() {
  fast_io();

  int a[5];
  for (int i = 0; i < 5; i++) cin >> a[i];

  int ans = 1e9;
  for (int i = 0; i < 5; i++) {
    for (int j = i + 1; j < 5; j++) {
      for (int k = j + 1; k < 5; k++) {
        ans = min(ans, lcm(a[i], lcm(a[j], a[k])));
      }
    }
  }

  cout << ans << '\n';
}
