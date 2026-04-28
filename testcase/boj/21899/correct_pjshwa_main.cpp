#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, MAXQ = 400;
int P[MAXN + 1], D[MAXQ + 1][MAXN + 1];

void solve() {
  int N, T; cin >> N >> T;
  for (int i = 0; i < N; ++i) {
    int ai, bi; cin >> ai >> bi;
    if (bi > MAXQ) for (int t = ai; t <= T; t += bi) ++P[t];
    else ++D[bi][ai];
  }
  for (int g = 1; g <= MAXQ; ++g) for (int s = 0; s < g; ++s) {
    int t = s, v = 0;
    while (t <= T) {
      v += D[g][t];
      P[t] += v;
      t += g;
    }
  }

  for (int t = 1; t <= T; ++t) cout << P[t] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
