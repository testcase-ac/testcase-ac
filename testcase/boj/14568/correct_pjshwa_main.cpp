#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, ans = 0; cin >> N;
  for (int a = 2; a <= N; a += 2) for (int b = 1; a + b <= N; ++b) {
    int c = N - a - b;
    ans += c >= b + 2;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
