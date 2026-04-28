#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
double P[MAXN], R[MAXN];
int vis[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> P[i] >> R[i], R[i] -= 1;

  double ans = 0;
  for (int it = 0; it < N; ++it) {
    int u = -1; double val = -1;
    for (int i = 0; i < N; ++i) {
      if (vis[i]) continue;
      if (val < P[i] * R[i]) {
        val = P[i] * R[i];
        u = i;
      }
    }
    vis[u] = 1; ans += P[u];
    for (int i = 0; i < N; ++i) {
      if (vis[i]) continue;
      P[i] *= (1 + R[i]);
    }
  }
  cout << fixed << setprecision(2) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
