#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int phi(int n) {
  int ret = n;
  for (int f = 2; f * f <= n; f++) {
    if (n % f) continue;

    ret -= ret / f;
    while (n % f == 0) n /= f;
  }
  if (n > 1) ret -= ret / n;
  return ret;
}

void solve() {
  int N; cin >> N;
  if (N == 1) return cout << "0\n", void();
  if (N == 2) return cout << "1\n", void();

  int ans = phi(N);
  if (N % 2 == 0) ans += phi(N / 2);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
