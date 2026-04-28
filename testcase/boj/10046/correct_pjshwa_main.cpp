#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4, INF = 0x3f3f3f3f;
int P[MAX], C[MAX], E[MAX];
int d[MAX + 1];

void solve() {
  int M, N; cin >> M >> N;
  for (int i = 0; i < M; i++) cin >> P[i];
  for (int i = 0; i < N; i++) cin >> C[i] >> E[i];

  memset(d, 0x3f, sizeof(d)); d[0] = 0;
  for (int i = 0; i < N; i++) {
    for (int v = MAX; v >= 0; v--) {
      int pv = max(0, v - C[i]);
      d[v] = min(d[v], d[pv] + E[i]);
    }
  }

  sort(P, P + M, greater<int>()); int acc = 0, ans = 0;
  for (int i = 1; i <= M; i++) {
    acc += P[i - 1];
    if (d[i] != INF) ans = max(ans, acc - d[i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
