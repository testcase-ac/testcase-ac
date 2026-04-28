#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXV = 5e5, INF = 0x3f3f3f3f;

void solve() {
  int N, M; cin >> N >> M;

  vector<tuple<int, int, int, int, int, int>> A;
  for (int i = 0; i < N; ++i) {
    int X, Y, Sm, Pm, Sv, Pv; cin >> X >> Y >> Sm >> Pm >> Sv >> Pv;
    A.emplace_back(X, Y, Sm, Pm, Sv, Pv);
  }

  int l = 1, r = 2 * M + 1;
  while (l < r) {
    int m = (l + r) / 2;

    ll cost = 0;
    for (int i = 0; i < N; ++i) {
      auto [X, Y, Sm, Pm, Sv, Pv] = A[i];
      int need = m * X - Y;
      if (need <= 0) continue;

      ll mcost = INF;
      for (int vc = 0;; ++vc) {
        ll cost = Pv * vc;
        int rem = need - vc * Sv;
        if (rem > 0) {
          int mc = rem / Sm + (rem % Sm != 0);
          cost += mc * Pm;
          mcost = min(mcost, cost);
        }
        else {
          mcost = min(mcost, cost);
          break;
        }
      }
      cost += mcost;
    }

    if (cost <= M) l = m + 1;
    else r = m;
  }

  cout << l - 1 << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
