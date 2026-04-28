#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N, M;
void solve() {
  ll ans = 0;
  for (ll s = 1; s <= min(N, M); s += 2) {
    ans += s * (N - s + 1) * (M - s + 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
