#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll nC3(ll n) {
  return n * (n - 1) * (n - 2) / 6;
}

void solve() {
  int N, M; cin >> N >> M;

  ll ans = nC3((N + 1) * (M + 1));
  ans -= nC3(M + 1) * (N + 1);
  ans -= nC3(N + 1) * (M + 1);
  for (int w = 1; w <= N; ++w) for (int h = 1; h <= M; ++h) {
    int g = gcd(w, h);
    ans -= 2LL * (g - 1) * (N - w + 1) * (M - h + 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
