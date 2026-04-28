#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10, INF = 1e9 + 7;
set<int> P[MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= M; i++) {
    int Oi;
    cin >> Oi;
    while (Oi--) {
      int Pj;
      cin >> Pj;
      P[i].insert(Pj);
    }
  }

  int ans = INF;
  for (int state = 0; state < (1 << M); state++) {
    set<int> cur;
    for (int i = 0; i < M; i++) {
      if (state & (1 << i)) {
        for (int j : P[i + 1]) cur.insert(j);
      }
    }

    if (cur.size() == N) ans = min(ans, __builtin_popcount(state));
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
