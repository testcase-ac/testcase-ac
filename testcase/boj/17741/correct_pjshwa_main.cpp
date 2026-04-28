#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 4000, BIAS = 2000, INF = 1e18;
ll d[MAX + 10][MAX + 10];
ll A[MAX + 10], B[MAX + 10];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i] >> B[i];

  for (int i = 0; i <= N; i++) {
    fill(d[i], d[i] + MAX + 10, -INF);
  }
  d[0][BIAS + 1] = 0;

  for (int i = 1; i <= N; i++) {
    for (int v = -BIAS; v <= BIAS; v++) {
      d[i][v + BIAS] = d[i - 1][v + BIAS];
    }

    for (int v = -BIAS; v <= BIAS; v++) {
      int nv = max(-BIAS, min(BIAS, v - 1 + A[i]));
      d[i][nv + BIAS] = max(d[i][nv + BIAS], d[i - 1][v + BIAS] + B[i]);
    }
  }

  ll ans = 0;
  for (int v = 0; v <= BIAS; v++) ans = max(ans, d[N][v + BIAS]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
