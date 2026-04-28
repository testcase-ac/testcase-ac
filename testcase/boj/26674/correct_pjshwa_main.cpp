#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int P[3][MAXN + 5];

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int l, r, k; cin >> l >> r >> k; --k;
    P[k][l]++; P[k][r + 1]--;
  }

  int ans = 0, X[3]{};
  for (int i = 1; i <= N; ++i) {
    for (int k = 0; k < 3; ++k) X[k] += P[k][i];
    ans += (X[0] > 0 && X[1] > 0 && X[2] == 0);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
