#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const ll INF = 1e18;
int S[MAX + 1], P[MAX + 1];
ll d[MAX + 1][501];

void solve() {
  int C, E, D, N;
  cin >> C >> E >> D >> N;

  for (int i = 1; i <= N; i++) cin >> S[i], S[i] += S[i - 1];
  for (int i = 1; i <= N; i++) cin >> P[i];

  for (int i = 1; i <= N; i++) fill(d[i], d[i] + 501, INF);
  d[0][C] = 0;

  for (int i = 1; i <= N; i++) {
    int used = (S[i] - S[i - 1]) * E;
    for (int o = 0; o <= C; o++) for (int v = used; v <= C; v++) {
      int addend = o - (v - used);
      if (addend < 0) continue;

      d[i][o] = min(d[i][o], d[i - 1][v] + addend * P[i]);
    }
  }

  int used = (D - S[N]) * E;
  ll ans = INF;
  for (int v = used; v <= C; v++) ans = min(ans, d[N][v]);

  if (ans == INF) cout << -1 << '\n';
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
