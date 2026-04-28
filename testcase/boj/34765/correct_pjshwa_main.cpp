#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, K, ans = 0; cin >> N >> K;
  for (ll o = 1; o <= N; ++o) {
    int Vt = K + N - o;
    int Vb = Vt - o + 1;
    ans = max(ans, (Vt + Vb) / 2 * o);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
