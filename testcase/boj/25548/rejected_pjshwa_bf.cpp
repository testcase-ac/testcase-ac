#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll f(ll A, ll B) {
  if (A > B || B % A) return 0;

  int U = B / A, ans = 0;
  for (int f = 1; f * f <= U; f++) {
    if (U % f) continue;
    int s = U / f;
    ans++;
    if (f != s) ans++;
  }
  return ans;
}

void solve() {
  int N;
  cin >> N;

  ll ans = 0;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) ans += f(i, j);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
