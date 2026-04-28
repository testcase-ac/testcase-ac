#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
ll B[MAX + 1], C[MAX + 1], P[MAX + 1][MAX + 1], W[MAX + 1][MAX + 1];
ll coef[MAX + 1];

void solve() {
  int N, M, Q;
  cin >> N >> M >> Q;
  for (int i = 1; i <= M; i++) {
    cin >> C[i];
    for (int j = 1; j <= C[i]; j++) cin >> P[i][j];
    for (int j = 1; j <= C[i]; j++) cin >> W[i][j];
    cin >> B[i];
  }

  for (int i = 1; i <= M; i++) {
    int x;
    cin >> x;
    for (int j = 1; j <= C[i]; j++) W[i][j] *= x;
    B[i] *= x;
  }

  ll tbias;
  cin >> tbias;
  for (int i = 1; i <= M; i++) tbias += B[i];
  for (int i = 1; i <= M; i++) {
    for (int j = 1; j <= C[i]; j++) coef[P[i][j]] += W[i][j];
  }

  while (Q--) {
    ll x, res = tbias;
    for (int i = 1; i <= N; i++) {
      cin >> x;
      res += x * coef[i];
    }
    cout << res << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
