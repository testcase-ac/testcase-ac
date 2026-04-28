#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, INF = 0x3f3f3f3f;
int d[MAX + 1][4], A, B, C;

int r(int v, int w) {
  if (v == 0) return d[v][w] = w == 0 ? 0 : INF;
  if (d[v][w] != -1) return d[v][w];

  int ret = INF;
  if (v >= A) ret = min(ret, r(v - A, (w + 3) % 4) + 1);
  if (v >= B) ret = min(ret, r(v - B, (w + 1) % 4) + 1);
  if (v >= C) ret = min(ret, r(v - C, (w + 2) % 4) + 1);
  return d[v][w] = ret;
}

void solve() {
  int K;
  cin >> A >> B >> C >> K;

  memset(d, -1, sizeof(d));
  int ans = r(K, 0);
  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
