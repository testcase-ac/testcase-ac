#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 20, INF = 0x3f3f3f3f;
int D[MAX], d[1 << MAX];
vector<int> S[MAX];

void solve() {
  int N, L; cin >> N >> L;
  for (int i = 0; i < N; i++) {
    int C, x; cin >> D[i] >> C;
    while (C--) cin >> x, S[i].push_back(x);
  }

  int ans = INF;
  for (int s = 0; s < (1 << N); s++) {
    if (d[s] >= L) ans = min(ans, __builtin_popcount(s));

    for (int i = 0; i < N; i++) {
      if (s & (1 << i)) continue;

      int ns = s | (1 << i);
      auto it = upper_bound(S[i].begin(), S[i].end(), d[s]);
      if (it == S[i].begin()) continue;

      d[ns] = max(d[ns], D[i] + *(prev(it)));
    }
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
