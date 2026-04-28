#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 20, MAXV = 150, MAXW = 150, INF = 0x3f3f3f3f;
pii A[MAX];
int d[MAXV + 1][MAXW + 1], N;

int r(int v, int w) {
  if (d[v][w] != -1) return d[v][w];
  if (v == 0 && w == 0) return d[v][w] = 0;

  int ret = INF;
  for (int i = 0; i < N; i++) {
    auto [dv, dw] = A[i];
    int nv = v - dv, nw = w - dw;
    if (nv < 0 || nw < 0) continue;
    ret = min(ret, r(nv, nw) + 1);
  }
  return d[v][w] = ret;
}

void solve() {
  int V, W; cin >> N >> V >> W;
  for (int i = 0; i < N; i++) {
    int v, w; cin >> v >> w;
    A[i] = {v, w};
  }

  memset(d, -1, sizeof(d));
  int ans = r(V, W);
  if (ans >= INF) ans = 0;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
