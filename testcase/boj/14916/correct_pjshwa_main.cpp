#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N; cin >> N;

  int ans = INF;
  for (int i = 0; i < 5; i++) {
    if (2 * i > N) continue;

    int rem = N - 2 * i;
    if (rem % 5) continue;

    ans = min(ans, i + rem / 5);
  }

  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
