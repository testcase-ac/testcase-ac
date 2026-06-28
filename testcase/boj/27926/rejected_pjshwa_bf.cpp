#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
map<pii, ll> A;

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < M; i++) {
    int u, v, d; cin >> u >> v >> d;
    A[{u, v}] = d;
    A[{v, u}] = d;
  }

  ll ans = 0;
  for (int a = 1; a <= N; a++) for (int b = 1; b <= N; b++) for (int c = 1; c <= N; c++)
  for (int d = 1; d <= N; d++) {
    if (a == b || a == c || a == d || b == c || b == d || c == d) continue;

    ans = max(ans, A[{a, b}] + A[{b, c}] + A[{c, d}]);
    // if (A[{a, b}] + A[{b, c}] + A[{c, d}] == 17) cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << ", ans = " << ans << endl;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
