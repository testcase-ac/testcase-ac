#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N;
  cin >> N;

  int ans = INF;
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    if (a <= b) ans = min(ans, b);
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
