#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000, MAXV = 2e6, BIAS = 1e6;
ll A[MAX + 1], E[MAX + 1][MAX + 1];
int C[MAXV + 10];

void solve() {
  int N, Q; cin >> N >> Q;

  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 1; i <= N; i++) {
    for (int j = i + 1; j <= N; j++) {
      int seek = -(A[i] + A[j]) + BIAS;
      if (0 <= seek && seek <= MAXV) E[i][j] = C[seek];
      C[A[j] + BIAS]++;
    }
    for (int j = i + 1; j <= N; j++) C[A[j] + BIAS]--;
  }

  for (int d = 2; d < N; d++) {
    for (int l = 1; l <= N; l++) {
      int r = l + d;
      if (r > N) break;
      E[l][r] += E[l + 1][r] + E[l][r - 1] - E[l + 1][r - 1];
    }
  }

  while (Q--) {
    int l, r; cin >> l >> r;
    cout << E[l][r] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
