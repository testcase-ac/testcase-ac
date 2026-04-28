#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300;
int board[MAX][MAX];

ll nC2(int n) {
  return n * (n - 1) / 2;
}

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> board[i][j];

  ll total = nC2(n + 1) * nC2(n + 1);
  double ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    double d1 = 0, d0 = 0;
    board[i][j] ? d1 = 1 : d0 = 1;

    ll chosen = (ll)(i + 1) * (n - i) * (j + 1) * (n - j);
    double choose_prob = (double)chosen / total;

    for (int it = 1; it <= k; it++) {
      double nd1 = d1 * (1 - choose_prob) + d0 * choose_prob;
      double nd0 = d1 * choose_prob + d0 * (1 - choose_prob);
      d1 = nd1, d0 = nd0;
    }

    ans += d1;
  }

  cout << fixed << setprecision(5) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
