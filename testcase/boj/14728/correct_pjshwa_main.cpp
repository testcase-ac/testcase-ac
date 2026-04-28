#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXV = 1e4, INF = 0x3f3f3f3f;
int d[MAXV + 1];

void solve() {
  int N, T; cin >> N >> T;
  fill(d, d + MAXV + 1, -INF); d[0] = 0;
  for (int i = 1; i <= N; i++) {
    int K, S; cin >> K >> S;
    for (int v = T; v >= K; v--) {
      d[v] = max(d[v], d[v - K] + S);
    }
  }
  
  int ans = 0;
  for (int v = 0; v <= T; v++) ans = max(ans, d[v]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
