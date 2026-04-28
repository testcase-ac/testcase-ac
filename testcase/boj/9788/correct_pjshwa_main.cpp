#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 400, INF = 0x3f3f3f3f;
int A[MAX + 1], U[MAX + 1][MAX + 1], D[MAX + 1][MAX + 1];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 1; i <= N; i++) cin >> A[i];

  for (int i = 1; i <= N; i++) {
    int maxx = -INF, minx = INF;
    for (int j = i; j <= N; j++) {
      maxx = max(maxx, A[j]);
      minx = min(minx, A[j]);
      U[i][j] = maxx - minx;
    }
  }

  for (int i = 0; i <= N; i++) for (int k = 0; k <= K; k++) D[i][k] = INF;
  D[0][0] = 0;
  for (int k = 1; k <= K; k++) {
    for (int i = 1; i <= N; i++) {
      for (int j = 0; j < i; j++) {
        D[i][k] = min(D[i][k], D[j][k - 1] + U[j + 1][i]);
      }
    }
  }

  cout << D[N][K] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
