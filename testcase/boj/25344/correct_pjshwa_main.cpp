#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int lcm(int a, int b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  int N;
  cin >> N;

  int ans = 1;
  for (int i = 0; i < N - 2; i++) {
    int x;
    cin >> x;
    ans = lcm(ans, x);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
